/*
  ==============================================================================

    EnvelopePanel.h
    Created: 20 Oct 2020 8:03:47pm
    Author: kyle 

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "BLXLookAndFeel.h"
#include "EnvelopeSliders.h"

class EnvelopePanel : public juce::Component
{
public:
    EnvelopePanel();

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    juce::Label panelLabel;
    EnvelopeSliders sliders;

};
