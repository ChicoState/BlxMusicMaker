/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Menu.h"
#include "InstrumentWindow.h"
//==============================================================================
/**
*/
class BlxMusicMakerAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    BlxMusicMakerAudioProcessorEditor (BlxMusicMakerAudioProcessor&);
    ~BlxMusicMakerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BlxMusicMakerAudioProcessor& audioProcessor;
    
    Menu menu;
    InstrumentWindow instrumentWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlxMusicMakerAudioProcessorEditor)
};









