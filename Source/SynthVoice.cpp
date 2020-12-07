#include <JuceHeader.h>
#include <cmath>

#include "SynthSound.h"
#include "maximilian.h"
#include "SynthVoice.h"


// connection between processor and voice
bool SynthVoice::getParam(
	std::atomic<float>* wave,	 std::atomic<float>* attack,
	std::atomic<float>* decay,	 std::atomic<float>* sustain,
	std::atomic<float>* release, std::atomic<float>* tremTog,
	std::atomic<float>* tremSpd, std::atomic<float>* tremDep,
	std::atomic<float>* vibrTog, std::atomic<float>* vibrSpd,
	std::atomic<float>* vibrDep, std::atomic<float>* noslTog,
	std::atomic<float>* noslSpd, std::atomic<float>* noslDep,
	double bpm
)
{
	if (wave == nullptr	   || attack == nullptr  ||
		decay == nullptr   || sustain == nullptr ||
		release == nullptr || tremTog == nullptr ||
		tremSpd == nullptr || tremDep == nullptr ||
		vibrTog == nullptr || vibrSpd == nullptr ||
		vibrDep == nullptr || noslTog == nullptr ||
		noslSpd == nullptr || noslDep == nullptr)
	{
		return false;
	}

	// wave
	curWaveFlag = (waveFlag)(int) *wave;

	// adsr
	env.setAttack(*attack);
	env.setDecay(*decay);
	env.setSustain(*sustain);
	env.setRelease(*release);

	// tremolo
	tremoloActive = *tremTog > 0.5f;
	tremoloDurFlag = (durationFlag)(int) *tremSpd;
	tremoloDepth = (double) *tremDep;

	// vibrato
	vibratoActive = *vibrTog > 0.5f;
	vibratoDurFlag = (durationFlag)(int) *vibrSpd;

	int vibratoDepth = (int) *vibrDep;
	double famitrackerIncrement = 0.93 * vibratoDepth;
	double midiNoteHertz = juce::MidiMessage::getMidiNoteInHertz(midiNoteNum);
	vibratoMaxFreq = midiNoteHertz + famitrackerIncrement;
	vibratoMinFreq = midiNoteHertz - famitrackerIncrement;

	// note slide
	int targetMidiOffset = (int) *noslDep; // in half-steps
	noteSlideTargetFreq = juce::MidiMessage::getMidiNoteInHertz(
		midiNoteNum + targetMidiOffset); 
	noteSlideActive = *noslTog > 0.5f;
	noteSlideDurFlag = (durationFlag) (int) *noslSpd;

	this->bpm = bpm;
	return true;
}

void SynthVoice::setMaxiSettings(double sampleRate, double channels,
	double bufferSize)
{
	set.setup(sampleRate, channels, bufferSize);
}

void SynthVoice::startNote(int midiNoteNumber, float velocity,
	juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
	// reset adsr phases 
	env.setTrigger(1);
	env.holdphase = 0;
	env.attackphase = 0;
	env.decayphase = 0;
	env.sustainphase = 0;
	env.releasephase = 0;

	level = velocity;		// setting the volume
	osc.phaseReset(0.0);    // reset delta-theta
	midiNoteNum = midiNoteNumber;
	freq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNum);

	// for note slide
	originalFreq = freq;
	noteSlideTimer = 0; // start time for note slide

	// for tremolo
	tremoloOsc.phaseReset(0.0);
	startLevel = level;

	// for vibrato
	vibratoOsc.phaseReset(0.0);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample,
	int numSamples)
{
	for (int sample = 0; sample < numSamples; ++sample)
	{
		// osc the volume 
		if (tremoloActive)
		{
			level = startLevel + tremoloDepth * tremoloOsc.sinewave(convertDuration(tremoloDurFlag));
			if (level < 0) level = 0;
		}

		// osc the pitch 
		if (vibratoActive)
		{
			double amp = (vibratoMaxFreq - vibratoMinFreq) * 0.5;
			double offset = (vibratoMaxFreq + vibratoMinFreq) * 0.5;
			freq = offset + amp * vibratoOsc.sinewave(convertDuration(vibratoDurFlag));
		}

		// slide the note
		if (noteSlideActive)
		{
			double deltaTime = 1.0 / getSampleRate();
			double duration = getNoteSlideDuration();
			if (noteSlideTimer < duration)
				freq += (noteSlideTargetFreq - originalFreq) / duration * deltaTime;
			noteSlideTimer += deltaTime;
		}

		double theSound = env.adsr(getOscType(), env.getTrigger()) * level;
		if (env.getTrigger() == 0) clearCurrentNote();

		if (curWaveFlag == waveFlag::Noise)
		{
			double midiKeyNum = 1.0 + midiNoteNum % 12;
			theSound = fil.lores(theSound, 500 * midiKeyNum, 0.1f * midiKeyNum);
		}

		for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			outputBuffer.addSample(channel, startSample, theSound);
		++startSample;
	}
}

float SynthVoice::getOscType()
{
	switch (curWaveFlag)
	{
	case waveFlag::Saw:
		return osc.saw(freq); break;
	case waveFlag::Noise:
		return osc.noise(); break;
	case waveFlag::Triangle:
		return osc.triangle(freq); break;
	case waveFlag::Pulse25:
		return osc.pulse(freq, 0.25); break;
	case waveFlag::Pulse50:
		return osc.pulse(freq, 0.5); break;
	case waveFlag::Pulse75:
		return osc.pulse(freq, 0.75); break;
	default:
		return osc.sinewave(freq); break;
	}
}

double SynthVoice::getNoteSlideDuration()
{
	switch (noteSlideDurFlag)
	{
	case durationFlag::Whole:
		return 4 * (60 / bpm);
	case durationFlag::Half:
		return 2 * (60 / bpm);
	case durationFlag::Quarter:
		return 1 * (60 / bpm);
	case durationFlag::Eighth:
		return 0.5 * (60 / bpm);
	case durationFlag::Sixteenth:
		return 0.25 * (60 / bpm);
	default: //case durationFlag::Thirtysecond:
		return 0.125 * (60 / bpm);
	}
}

double SynthVoice::convertDuration(durationFlag flag)
{
	switch (flag)
	{
	case durationFlag::Whole:
		return 0.5 * (60 / bpm);
	case durationFlag::Half:
		return 1 * (60 / bpm);
	case durationFlag::Quarter:
		return 2 * (60 / bpm);
	case durationFlag::Eighth:
		return 4 * (60 / bpm);
	case durationFlag::Sixteenth:
		return 8 * (60 / bpm);
	default: //case durationFlag::Thirtysecond:
		return 16 * (60 / bpm);
	}
}
