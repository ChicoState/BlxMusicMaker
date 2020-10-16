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

class SynthVoice : public juce::SynthesiserVoice
{
public:

    //Do not change the order
    enum waveFlag{ Square, Triangle, Saw, Sine, Noise};
    static waveFlag currentWaveFlag;

    bool canPlaySound(juce::SynthesiserSound* sound) 
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    // connection between processor and voice
    void getParam(float attack, float decay, float sustain, float release)
    {
        env1.setAttack(attack);
        env1.setDecay(decay);
        env1.setSustain(sustain);
        env1.setRelease(release);
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
        int currentPitchWheelPosition)
    {
        env1.trigger = 1; // means envolope starts
        level = velocity; // setting the volume
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber); // finding the key pressed
    }

    void stopNote(float velocity, bool allowTailOff) 
    {
        env1.trigger = 0;
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
			case SynthVoice::Sine:
				theWave = osc1.sinewave(frequency);
				break;
			case SynthVoice::Saw:
				theWave = osc1.saw(frequency);
				break;
			case SynthVoice::Noise:
				theWave = osc1.noise(); 
				break;
			case SynthVoice::Triangle:
				theWave = osc1.triangle(frequency);
				break;
			case SynthVoice::Square:
				theWave = osc1.square(frequency);
				break;
			default:
				theWave = osc1.sinewave(frequency);
				std::cerr << "This should not have happened. Default case for currentSineFlag triggered; setting sine value to SINE";
				break;
			}
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            double filteredSound = fil1.lores(theSound, 500, 0.1); //TODO low/high pass filter

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                // if you want to filter the sound, then replace theSound with filteredSound
                outputBuffer.addSample(channel, startSample, filteredSound); 
            }
            ++startSample;
        }
    }

private:
    double level;
    double frequency;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter fil1;
};

















