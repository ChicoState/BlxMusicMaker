/*
  ==============================================================================

    SliderComponent.cpp
    Created: 28 Oct 2020 2:24:18pm
    Author: kyle 

  ==============================================================================
*/

#include "SliderComponent.h"

SliderComponent::SliderComponent(std::string text, std::string stateID)
{
	label.setText(text, juce::NotificationType::dontSendNotification);
	addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, 50, 20);
    slider.setNumDecimalPlacesToDisplay(0);
    sliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*StateManager::get().treeState, stateID, slider));
    addAndMakeVisible(slider);
}

void SliderComponent::paint(juce::Graphics&)
{
}

void SliderComponent::resized()
{
    auto area = getLocalBounds();
    label.setBounds(area.removeFromLeft(80));
    slider.setBounds(area);
}
