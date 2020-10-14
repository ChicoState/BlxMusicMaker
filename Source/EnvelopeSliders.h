/*
  ==============================================================================

    EnvelopeSliders.h
    Created: 13 Oct 2020 9:28:54pm
    Author:  alext

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class EnvelopeSliders : public juce::Component
{
public:
    EnvelopeSliders();
    ~EnvelopeSliders() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(int);

private:
    juce::Slider* sliders;
    juce::Label* labels;

};

