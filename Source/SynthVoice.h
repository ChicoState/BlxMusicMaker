/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Oct 2020 7:19:15pm
    Author:  alext

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "maximilian.h"
#include "StateManager.h"
#include <cmath>

class SynthVoice : public juce::SynthesiserVoice
{
public:

    bool canPlaySound(juce::SynthesiserSound* sound) 
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    // connection between processor and voice
    void getParam(float attack, float decay, float sustain, float release,
        double bpm, int timeSigNum, int timeSigDenom)
    {
        env.setAttack(attack);
        env.setDecay(decay);
        env.setSustain(sustain);
        env.setRelease(release);

        this->bpm = bpm;
        this->timeSigNum = timeSigNum;
        this->timeSigDenom = timeSigDenom;
    }

    void setMaxiSettings(double sampleRate, double channels, double bufferSize)
    {
        set.setup(sampleRate, channels, bufferSize);
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
        int currentPitchWheelPosition)
    {
        // init class vars
        env.setTrigger(1);
        env.holdphase = 0;
        env.attackphase = 0;
        env.decayphase = 0;
        env.sustainphase = 0;
        env.releasephase = 0;

        level = velocity * 0.15;// setting the volume
        osc.phaseReset(0.0);    // reset delta-theta
        midiNoteNum = midiNoteNumber;
        freq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNum);

        // for note slide
        setNoteSlideFromTree();
		originalFreq = freq;
        noteSlideTimer = 0; // start time for note slide

        // for tremolo
		tremoloOsc.phaseReset(0.0);
        startLevel = level;

        // for vibrato
        vibratoOsc.phaseReset(0.0);
    }

    void stopNote(float velocity, bool allowTailOff) 
    {
    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample,
        int numSamples)
    {
        setTremoloFromTree();
        setVibratoFromTree();
        setWaveFromTree();
        if (getTremoloDuration() > 0) std::cerr << "note duration trem : " << getTremoloDuration() << std::endl;
        if (getNoteSlideDuration() > 0) std::cerr << "note duration note slide : " << getNoteSlideDuration() << std::endl;

		for (int sample = 0; sample < numSamples; ++sample)
		{
			// osc the volume 
            if (tremoloActive)
            {
                level = startLevel + tremoloDepth * tremoloOsc.sinewave(getTremoloDuration());
                if (level < 0) level = 0;
            }

            if (vibratoActive)
            {
                double amp = (vibratoMaxFreq - vibratoMinFreq) * 0.5;
                double offset = (vibratoMaxFreq + vibratoMinFreq) * 0.5;
                freq = offset + amp * vibratoOsc.sinewave(getVibratoDuration());
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

    void pitchWheelMoved(int newPitchWheelValue) { }
    void controllerMoved(int controllerNumber, int newControllerValue) { }

private:
    int midiNoteNum;
    double level;               // volume
    double freq;                // cycles per second
    double bpm, timeSigNum, timeSigDenom; 

    // note slide vars
    bool noteSlideActive;
    double originalFreq, noteSlideTargetFreq, noteSlideTimer;
    
    // tremolo vars
    bool tremoloActive;
    double tremoloDepth;
    double startLevel;
    maxiOsc tremoloOsc;

    // vibrato vars
    bool vibratoActive;
    int vibratoDepth;
    double vibratoMaxFreq, vibratoMinFreq;
    maxiOsc vibratoOsc;
        
    maxiOsc osc;
    maxiEnv env;
    maxiFilter fil;
    maxiSettings set;

	enum class waveFlag{ Pulse25, Pulse50, Pulse75, Triangle, Saw, Sine, Noise };
	enum class durationFlag{ Thirtysecond, Sixteenth, Eighth, Quarter, Half, Whole };

    waveFlag curWaveFlag;
    durationFlag curTremoloDurFlag;
    durationFlag curNoteSlideDurFlag;
    durationFlag curVibratoDurFlag;

    // gets values from tree and updates synth voice accordingly
    void setNoteSlideFromTree()
    {
        std::atomic<float>* nsOn =
            StateManager::get().treeState->getRawParameterValue("Note Slide");
	    std::atomic<float>* nsSpe =
            StateManager::get().treeState->getRawParameterValue("NoteSlideSpeed");
	    std::atomic<float>* nsDep =
            StateManager::get().treeState->getRawParameterValue("NoteSlideDepth");

        if (nsOn == nullptr || nsSpe == nullptr || nsDep == nullptr)
        {
            std::cerr << "note slide thing is null." << std::endl;
            return;
        }

		int targetMidiOffset = (int) *nsDep; // in half-steps
		noteSlideTargetFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNum + targetMidiOffset); 
        noteSlideActive = *nsOn > 0.5f;
		curNoteSlideDurFlag = (durationFlag) (int) *nsSpe;
    }
    
    void setTremoloFromTree()
    {
        std::atomic<float>* tremOn =
            StateManager::get().treeState->getRawParameterValue("Tremolo");
	    std::atomic<float>* tremSpe =
            StateManager::get().treeState->getRawParameterValue("TremoloSpeed");
	    std::atomic<float>* tremDep =
            StateManager::get().treeState->getRawParameterValue("TremoloDepth");

        if (tremOn == nullptr || tremSpe == nullptr || tremDep == nullptr)
        {
            std::cerr << "tremolo thing is null." << std::endl;
            return;
        }

        tremoloActive = *tremOn > 0.5f;
        curTremoloDurFlag = (durationFlag)(int) *tremSpe;
        tremoloDepth = (double) *tremDep;
    }

    void setVibratoFromTree()
    {
        std::atomic<float>* vibOn =
            StateManager::get().treeState->getRawParameterValue("Vibrato");
	    std::atomic<float>* vibSpe =
            StateManager::get().treeState->getRawParameterValue("VibratoSpeed");
	    std::atomic<float>* vibDep =
            StateManager::get().treeState->getRawParameterValue("VibratoDepth");

        if (vibOn == nullptr || vibSpe == nullptr || vibDep == nullptr)
        {
            std::cerr << "vibrato thing is null." << std::endl;
            return;
        }

        vibratoActive = *vibOn > 0.5f;
        curVibratoDurFlag = (durationFlag)(int) *vibSpe;

        int vibratoDepth = (int) *vibDep;
        double famitrackerIncrement = 0.93 * vibratoDepth;
        vibratoMaxFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNum) + famitrackerIncrement;
        vibratoMinFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNum) - famitrackerIncrement;
    }

    void setWaveFromTree()
    {
        std::atomic<float>* wave =
            StateManager::get().treeState->getRawParameterValue("Wave");
        if (wave == nullptr)
        {
            std::cerr << "wave thing is null." << std::endl;
            return;
        }
        curWaveFlag = (waveFlag)(int) *wave;
    }

    float getOscType()
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

    double getNoteSlideDuration()
    {
        if (!noteSlideActive) return 0.0;

		// math'ed out for 4/4 time
        switch (curNoteSlideDurFlag)
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
        case durationFlag::Thirtysecond:
            return 0.125 * (60 / bpm);
        }
    }

    double getTremoloDuration()
    {
        if (!tremoloActive) return 0.0;
		switch (curTremoloDurFlag)
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
		case durationFlag::Thirtysecond:
			return 16 * (60 / bpm);
		}
    }

    double getVibratoDuration()
    {
        if (!vibratoActive) return 0.0;
		switch (curVibratoDurFlag)
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
		case durationFlag::Thirtysecond:
			return 16 * (60 / bpm);
		}
    }

};
