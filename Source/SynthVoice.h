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
#include <cmath>


class SynthVoice : public juce::SynthesiserVoice
{
public:
    //Do not change the order
	enum class waveFlag{ Pulse25, Pulse50, Pulse75, Triangle, Saw, Sine, Noise };
	enum class tremoloDurFlag{ Whole, Half, Quarter, Eighth, Sixteenth, Thirtysecond };
	enum class noteSlideDurFlag{ Whole, Half, Quarter, Eighth };

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
        env.trigger = 1;        // means envolope starts
        level = velocity;       // setting the volume
        startLevel = level;
        osc.phaseReset(0.0);    // reset delta-theta
        timer = 0;              // start time for note slide
        freq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

        // tremolo
        // TODO manage thru UI
        tremoloActive = true;
        if (tremoloActive)
        {
            oscTremolo.phaseReset(0.0);
            depthTremolo = 0.5; 
            currentTremoloDurFlag = tremoloDurFlag::Thirtysecond;
            switch (currentTremoloDurFlag)
            {
            case tremoloDurFlag::Whole:
                durationTremolo = 0.5 * (60 / bpm);
                break;
            case tremoloDurFlag::Half:
                durationTremolo = 1 * (60 / bpm);
                break;
            case tremoloDurFlag::Quarter:
                durationTremolo = 2 * (60 / bpm);
                break;
            case tremoloDurFlag::Eighth:
                durationTremolo = 4 * (60 / bpm);
                break;
            case tremoloDurFlag::Sixteenth:
                durationTremolo = 8 * (60 / bpm);
                break;
			case tremoloDurFlag::Thirtysecond:
                durationTremolo = 16 * (60 / bpm);
                break;
            }
        }

        // note slide
        // TODO manage thru UI
        noteSlideActive = false;
        if (noteSlideActive)
        {
		    int targetMidiOffset = 7; // in half-steps
            currentNoteSlideDurFlag = noteSlideDurFlag::Eighth;

			// math'ed out for 4/4 time
            switch (currentNoteSlideDurFlag)
            {
            case noteSlideDurFlag::Whole:
				duration = 4 * (60 / bpm);
                break;
            case noteSlideDurFlag::Half:
				duration = 2 * (60 / bpm);
                break;
            case noteSlideDurFlag::Quarter:
				duration = 1 * (60 / bpm);
                break;
            case noteSlideDurFlag::Eighth:
				duration = 0.5 * (60 / bpm);
                break;
            }

            targetFreq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber+targetMidiOffset); 
            originalFreq = freq;
        }
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
        // slide the note
        if (noteSlideActive)
        {
			double deltaTime = outputBuffer.getNumSamples() / getSampleRate();
			timer += deltaTime;
			if (timer < duration)
				freq += (targetFreq - originalFreq) / duration * deltaTime;
        }

		for (int sample = 0; sample < numSamples; ++sample)
		{
            if (tremoloActive)
            {
                level = startLevel + depthTremolo * oscTremolo.sinewave(durationTremolo);
                if (level < 0) level = 0;
            }

			float theWave = getWave(); // the current sample
			double theSound = env.adsr(theWave, env.trigger) * level;

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
    double timer, duration;                 // for note slide
    double durationTremolo, depthTremolo;   // for tremolo
    double bpm, timeSigNum, timeSigDenom; 

    bool noteSlideActive;
    bool tremoloActive;

    maxiOsc osc;
    maxiOsc oscTremolo;
    maxiEnv env;
    maxiFilter fil;
    maxiSettings set;

    float getWave()
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
};



















