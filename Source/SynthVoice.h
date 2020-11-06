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
    enum waveFlag{ Pulse25, Pulse50, Pulse75, Triangle, Saw, Sine, Noise };
    static waveFlag currentWaveFlag;

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
        osc.phaseReset(0.0);    // reset delta-theta
        timer = 0;              // start time for note slide
        freq = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

        // note slide
        // TODO noteSlideActive, targetMidiOffset, durationType, managed by UI
        noteSlideActive = false; // activate note slide
        if (noteSlideActive)
        {
		    int targetMidiOffset = 7; // change where you're sliding by half-steps
			juce::String durationType = "1/8"; // TODO change to enum

			// math'ed out for 4/4 time
			if (durationType == "1")
				duration = 4 * (60 / bpm);
			else if (durationType == "1/2")
				duration = 2 * (60 / bpm);
			else if (durationType == "1/4")
				duration = 1 * (60 / bpm);
			else //if (durationType == "1/8")
				duration = 0.5 * (60 / bpm);

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
			float theWave; // the current sample
			switch (currentWaveFlag)
			{
			case SynthVoice::Saw:
				theWave = osc.saw(freq); break;
			case SynthVoice::Noise:
				theWave = osc.noise(); break;
			case SynthVoice::Triangle:
				theWave = osc.triangle(freq); break;
			case SynthVoice::Pulse25:
				theWave = osc.pulse(freq, 0.25); break;
			case SynthVoice::Pulse50:
				theWave = osc.pulse(freq, 0.5); break;
			case SynthVoice::Pulse75:
				theWave = osc.pulse(freq, 0.75); break;
			default:
				theWave = osc.sinewave(freq); break;
			}
			double theSound = env.adsr(theWave, env.trigger) * level;

			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
				outputBuffer.addSample(channel, startSample, theSound);
			++startSample;
		}
    }

    void pitchWheelMoved(int newPitchWheelValue) { }
    void controllerMoved(int controllerNumber, int newControllerValue) { }

private:
    double level; // volume
    double freq, originalFreq, targetFreq; // cycles per second
    double bpm, timeSigNum, timeSigDenom; 
    double timer, duration; // for note slide

    bool noteSlideActive;

    maxiOsc osc;
    maxiEnv env;
    maxiFilter fil;
    maxiSettings set;
};



















