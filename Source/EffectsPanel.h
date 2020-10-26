/*
  ==============================================================================

    EffectsPanel.h
    Created: 20 Oct 2020 8:04:06pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "BLXLookAndFeel.h"
#include "TypeSelector.h"

class EffectsPanel : public juce::Component
{
public:

    EffectsPanel();
    void paint(juce::Graphics&) override;
    void resized() override;

private:

    juce::Label panelLabel;

};
