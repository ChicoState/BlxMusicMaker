/*
  ==============================================================================

    SliderComponent.h
    Created: 28 Oct 2020 2:24:18pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SliderComponent : public juce::Component
{
public:

    SliderComponent(std::string text, int minValue, int maxValue);
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::Label label;
    juce::Slider slider;

};
