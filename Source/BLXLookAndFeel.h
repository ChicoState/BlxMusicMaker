/*
  ==============================================================================

    BLXLookAndFeel.h
    Created: 25 Oct 2020 3:55:39pm
    Author: kyle 

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
using namespace juce;

class BLXLookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    BLXLookAndFeel();
    static int getPanelLabelHeight();
    static juce::Rectangle<int> getEffectsInsetArea(juce::Rectangle<int>);
    static juce::Rectangle<int> getWaveInsetArea(juce::Rectangle<int>);
    static juce::Rectangle<int> getEnvelopeInsetArea(juce::Rectangle<int>);
    void drawMenuBarBackground (Graphics&, int width, int height, bool isMouseOverBar, MenuBarComponent&) override;

private:
    
};
