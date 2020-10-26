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
#include "TypeSelector.h"

class WavePanel : public juce::Component 
{
public:

    WavePanel();
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Label panelLabel;
    TypeSelector typeSelector;

};
