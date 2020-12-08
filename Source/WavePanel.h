/*
  ==============================================================================

    WavePanel.h
    Created: 20 Oct 2020 7:34:09pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "BLXLookAndFeel.h"
#include "WaveSelector.h"
#include "PluginProcessor.h"

class WavePanel : public juce::Component 
{
public:

    WavePanel(BlxMusicMakerAudioProcessor&);
    ~WavePanel();
    void paint(juce::Graphics&) override;
    void resized() override;

private:

    juce::Rectangle<int> getInsetArea(juce::Rectangle<int>);
    juce::Label panelLabel;
    TypeSelector* typeSelector;

};
