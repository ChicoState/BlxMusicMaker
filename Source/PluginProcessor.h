/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthVoice.h"
#include "SynthSound.h"

//==============================================================================
/**
*/
class BlxMusicMakerAudioProcessor : public juce::AudioProcessor, public juce::UnitTest
{
public:
    //==============================================================================
    BlxMusicMakerAudioProcessor();
    ~BlxMusicMakerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState treeState;
    juce::UndoManager undoManager;

private:

    // arp vars
    int time, currentNote, lastNoteValue;
    juce::SortedSet<int> notes;

    juce::Synthesiser mySynth;
    SynthVoice* myVoice;
    float lastSampleRate;

    // get info of DAW
    juce::AudioPlayHead* audioPlayHead; 
    juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;

    float getArpDuration(int);
    const int internalPresetCount = 4;
    juce::String internalPresetNames[4] = {"Internal1", "Internal2", "Internal3", "Internal4"};
    juce::ValueTree* preset;

    void runTest() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlxMusicMakerAudioProcessor)
};









