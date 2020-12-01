/*
  ==============================================================================

    SliderComponent.h
    Created: 28 Oct 2020 2:24:18pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class SliderComponent : public juce::Component
{
public:

    SliderComponent(std::string, std::string, BlxMusicMakerAudioProcessor&);
    void resized() override;

private:

    juce::Label label;
    juce::Slider slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;

};
