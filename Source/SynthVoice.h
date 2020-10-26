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
    void getParam(float attack, float decay, float sustain, float release)
    {
        env.setAttack(attack);
        env.setDecay(decay);
        env.setSustain(sustain);
        env.setRelease(release);
    }

    void initMaxiSampleRate(double sampleRate)
    {
        set.setSampleRate(sampleRate);
        //juce::Logger::writeToLog("maxi sample rate: " + juce::String(set.getSampleRate()));
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
        int currentPitchWheelPosition)
    {
        env.trigger = 1; // means envolope starts
        level = velocity; // setting the volume
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber); // finding the key pressed
        midiNoteLetter = midiNoteNumber % 12;
    }

    void stopNote(float velocity, bool allowTailOff) 
    {
        env.trigger = 0;
        allowTailOff = true;
        if (velocity == 0)
        {
            clearCurrentNote();
        }
    }

    void pitchWheelMoved(int newPitchWheelValue) 
    {

    }

    void controllerMoved(int controllerNumber, int newControllerValue) 
    {

    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample,
        int numSamples)
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
			float theWave;
			switch (currentWaveFlag)
			{
			case SynthVoice::Saw:
				theWave = osc.saw(frequency); break;
			case SynthVoice::Noise:
				theWave = osc.noise(); break;
			case SynthVoice::Triangle:
				theWave = osc.triangle(frequency); break;
			case SynthVoice::Pulse25:
				theWave = osc.pulse(frequency, 0.25); break;
			case SynthVoice::Pulse50:
				theWave = osc.pulse(frequency, 0.5); break;
			case SynthVoice::Pulse75:
				theWave = osc.pulse(frequency, 0.75); break;
			default:
				theWave = osc.sinewave(frequency); break;
			}
            double theSound = env.adsr(theWave, env.trigger) * level;
            //double filteredSound = fil.lores(theSound, 100, 0.1); //TODO low/high pass filter

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                // if you want to filter the sound, then replace theSound with filteredSound
                outputBuffer.addSample(channel, startSample, theSound); 
            }
            ++startSample;
        }
    }

private:
    double level;
    double frequency;
    int midiNoteLetter; // note C = 0, D = 1, etc

    maxiOsc osc;
    maxiEnv env;
    maxiFilter fil;
    maxiSettings set;
};

















