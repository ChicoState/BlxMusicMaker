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
    //Do not change the order
	enum class waveFlag{ Pulse25, Pulse50, Pulse75, Triangle, Saw, Sine, Noise };
	enum class tremoloDurFlag{ Thirtysecond, Sixteenth, Eighth, Quarter, Half, Whole };
	enum class noteSlideDurFlag{ Thirtysecond, Sixteenth, Eighth, Quarter, Half, Whole };

    static waveFlag currentWaveFlag;
    static tremoloDurFlag currentTremoloDurFlag;
    static noteSlideDurFlag currentNoteSlideDurFlag;

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
        setNoteSlideFromTree(midiNoteNumber);

        // init class vars
        env.trigger = 1;        // means envolope starts
        level = velocity;       // setting the volume
        startLevel = level;
        osc.phaseReset(0.0);    // reset delta-theta
		oscTremolo.phaseReset(0.0);
        timer = 0;              // start time for note slide
        freq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		originalFreq = freq;
    }

    void stopNote(float velocity, bool allowTailOff) 
    {
        env.trigger = 0;
		clearCurrentNote();
		osc.phaseReset(0.0);
    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample,
        int numSamples)
    {
        setTremoloFromTree();

		for (int sample = 0; sample < numSamples; ++sample)
		{
			// osc the volume 
            if (tremoloActive)
            {
                level = startLevel + depthTremolo * oscTremolo.sinewave(getTremoloDuration());
                if (level < 0) level = 0;
            }

			// slide the note
			if (noteSlideActive)
			{
				double deltaTime = 1.0 / getSampleRate();
                double duration = getNoteSlideDuration();
				if (timer < duration)
			        freq += (targetFreq - originalFreq) / duration * deltaTime;
				timer += deltaTime;
			}

			double theSound = env.adsr(getOscType(), env.trigger) * level;

			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
				outputBuffer.addSample(channel, startSample, theSound);
			++startSample;
		}
    }

    void pitchWheelMoved(int newPitchWheelValue) { }
    void controllerMoved(int controllerNumber, int newControllerValue) { }

private:
    double level, startLevel;               // volume
    double freq, originalFreq, targetFreq;  // cycles per second
    double timer;                 // for note slide
    double depthTremolo;   // for tremolo
    double bpm, timeSigNum, timeSigDenom; 

    bool noteSlideActive;
    bool tremoloActive;

    maxiOsc osc;
    maxiOsc oscTremolo;
    maxiEnv env;
    maxiFilter fil;
    maxiSettings set;

    // gets values from tree and updates synth voice accordingly
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
        currentTremoloDurFlag = (tremoloDurFlag)(int) *tremSpe;
        depthTremolo = (double) *tremDep;
    }

    void setNoteSlideFromTree(int midiNoteNumber)
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
		targetFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber+targetMidiOffset); 
        noteSlideActive = *nsOn > 0.5f;
		currentNoteSlideDurFlag = (noteSlideDurFlag) (int) *nsSpe;
    }

    float getOscType()
    {
		switch (currentWaveFlag)
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

    double getTremoloDuration()
    {
        if (!tremoloActive) return 0.0;
		switch (currentTremoloDurFlag)
		{
		case tremoloDurFlag::Whole:
			return 0.5 * (60 / bpm);
		case tremoloDurFlag::Half:
			return 1 * (60 / bpm);
		case tremoloDurFlag::Quarter:
			return 2 * (60 / bpm);
		case tremoloDurFlag::Eighth:
		    return 4 * (60 / bpm);
		case tremoloDurFlag::Sixteenth:
			return 8 * (60 / bpm);
		case tremoloDurFlag::Thirtysecond:
			return 16 * (60 / bpm);
		}
    }

    double getNoteSlideDuration()
    {
        if (!noteSlideActive) return 0.0;

		// math'ed out for 4/4 time
        switch (currentNoteSlideDurFlag)
        {
        case noteSlideDurFlag::Whole:
            return 4 * (60 / bpm);
        case noteSlideDurFlag::Half:
            return 2 * (60 / bpm);
        case noteSlideDurFlag::Quarter:
            return 1 * (60 / bpm);
        case noteSlideDurFlag::Eighth:
            return 0.5 * (60 / bpm);
        case noteSlideDurFlag::Sixteenth:
            return 0.25 * (60 / bpm);
        case noteSlideDurFlag::Thirtysecond:
            return 0.125 * (60 / bpm);
        }
    }
};
