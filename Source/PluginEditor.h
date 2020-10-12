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
class BlxMusicMakerAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    BlxMusicMakerAudioProcessorEditor (BlxMusicMakerAudioProcessor&);
    ~BlxMusicMakerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BlxMusicMakerAudioProcessor& audioProcessor;
    
    Menu* menu;
    InstrumentWindow* instrumentWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlxMusicMakerAudioProcessorEditor)
};









