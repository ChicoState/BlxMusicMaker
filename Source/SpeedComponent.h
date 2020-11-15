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

class SpeedComponent : public juce::Component
{
public:

    SpeedComponent(std::string stateID);
    void onSpeedToggle(int i);
    void onValueChange();
    void paint(juce::Graphics&) override;
    void resized() override;

private:

    juce::String stateID;
    juce::Label label;
    juce::TextButton buttons[6];

    juce::Slider speedSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedAttachment;

};
