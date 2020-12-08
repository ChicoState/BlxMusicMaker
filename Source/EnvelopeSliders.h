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
#include "BLXLookAndFeel.h"

class EnvelopeSliders : public juce::Component
{
public:

    EnvelopeSliders(BlxMusicMakerAudioProcessor&);
    void resized() override;

private:

    const int sliderCount = 4;
    juce::Slider sliders[4];
    juce::Label labels[4];
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment[4];

};

