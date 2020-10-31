/*
  ==============================================================================

    SpeedComponent.h
    Created: 28 Oct 2020 2:31:19pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "BLXLookAndFeel.h"

class SpeedComponent : public juce::Component
{
public:

    SpeedComponent();
    void paint(juce::Graphics&) override;
    void resized() override;
    enum SpeedValue{ eighth, quarter, half, whole };

    juce::Label label;
    juce::TextButton buttons[4];

};
