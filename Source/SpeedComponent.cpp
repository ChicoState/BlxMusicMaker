/*
  ==============================================================================

    SpeedComponent.cpp
    Created: 28 Oct 2020 2:31:19pm
    Author: kyle 

  ==============================================================================
*/

#include "SpeedComponent.h"

SpeedComponent::SpeedComponent(std::string text, std::string stateID, BlxMusicMakerAudioProcessor& p)
{
    this->stateID = stateID;

    label.setText(text, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, 50, 20);
    slider.setNumDecimalPlacesToDisplay(0);
    sliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(p.treeState, stateID, slider));
    addAndMakeVisible(slider);

    slider.onValueChange = [this] { onValueChange(); };
}

void SpeedComponent::paint(juce::Graphics&)
{
}

void SpeedComponent::resized()
{
    auto area = getLocalBounds();
    label.setBounds(area.removeFromLeft(80));
    slider.setBounds(area);
}

void SpeedComponent::onValueChange()
{
    slider.setTextValueSuffix("1/8");
}
