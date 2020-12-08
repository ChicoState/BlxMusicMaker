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
#include "PluginProcessor.h"

class SpeedSlider : public juce::Slider
{
    juce::String stringValues[6] = { "1/32", "1/16", "1/8", "1/4", "1/2", "1" };
    juce::String getTextFromValue(double value) override
    {
        return stringValues[(int)value];
    }
};

class SpeedComponent : public juce::Component
{
public:

    SpeedComponent(std::string, std::string, BlxMusicMakerAudioProcessor&);
    void resized() override;

private:

    juce::Label label;
    SpeedSlider slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;

};
