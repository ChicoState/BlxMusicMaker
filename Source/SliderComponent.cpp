/*
  ==============================================================================

    SliderComponent.cpp
    Created: 28 Oct 2020 2:24:18pm
    Author: kyle 

  ==============================================================================
*/

#include "SliderComponent.h"

SliderComponent::SliderComponent(std::string text, std::string stateID, BlxMusicMakerAudioProcessor& p)
{
    int sliderTextBoxWidth = 50;
    int sliderTextBoxHeight = 20;
    juce::Colour textBoxColor = BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::widgetBackground);

	label.setText(text, juce::NotificationType::dontSendNotification);
	addAndMakeVisible(label);
    slider.setColour(Slider::textBoxBackgroundColourId, textBoxColor);
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, sliderTextBoxWidth, sliderTextBoxHeight);
    slider.setNumDecimalPlacesToDisplay(0);
    sliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(p.treeState, stateID, slider));
    addAndMakeVisible(slider);
}

void SliderComponent::resized()
{
    int labelWidth = 80;
    auto area = getLocalBounds();
    label.setBounds(area.removeFromLeft(labelWidth));
    slider.setBounds(area);
}
