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
	void getParam(
		std::atomic<float>*, std::atomic<float>*, std::atomic<float>*, std::atomic<float>*,
		std::atomic<float>*, std::atomic<float>*, std::atomic<float>*, std::atomic<float>*,
		std::atomic<float>*, std::atomic<float>*, std::atomic<float>*, std::atomic<float>*,
		std::atomic<float>*, std::atomic<float>*, double);
	void setMaxiSettings(double sampleRate, double channels, double bufferSize);
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound,
		int currentPitchWheelPosition);
	void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample,
		int numSamples);

	void stopNote(float velocity, bool allowTailOff) {}
	void pitchWheelMoved(int newPitchWheelValue) {}
	void controllerMoved(int controllerNumber, int newControllerValue) {}
	bool canPlaySound(juce::SynthesiserSound* sound)
	{ return dynamic_cast<SynthSound*>(sound) != nullptr; } 

private:
	int midiNoteNum;
	double level, startLevel;   // volume
	double freq;                // cycles per second
	double bpm;

	// note slide vars
	bool noteSlideActive;
	double originalFreq, noteSlideTargetFreq, noteSlideTimer;

	// tremolo vars
	bool tremoloActive;
	double tremoloDepth;
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

	enum class waveFlag { Pulse25, Pulse50, Pulse75, Triangle, Saw, Sine, Noise };
	waveFlag curWaveFlag;

	enum class durationFlag { Thirtysecond, Sixteenth, Eighth, Quarter, Half, Whole };
	durationFlag tremoloDurFlag, noteSlideDurFlag, vibratoDurFlag;

	// gets values from tree and updates synth voice accordingly
	float getOscType();
	double getNoteSlideDuration();
	double convertDuration(durationFlag flag);
};
