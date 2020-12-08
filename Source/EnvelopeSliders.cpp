/*
  ==============================================================================

    EnvelopeSliders.cpp
    Created: 13 Oct 2020 9:28:54pm
    Author:  alext

  ==============================================================================
*/

#include "EnvelopeSliders.h"

EnvelopeSliders::EnvelopeSliders(BlxMusicMakerAudioProcessor& p)
{
	int textBoxWidth = 50;
	int textBoxHeight = 20;
	juce::Colour textBackgroundColor = BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::widgetBackground);
	std::string IDs[] = { "Attack", "Decay", "Sustain", "Release" };
	for (int i = 0; i < sliderCount; i++) 
	{
		sliders[i].setColour(Slider::textBoxBackgroundColourId, textBackgroundColor);
		sliders[i].setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		sliders[i].setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, textBoxWidth, textBoxHeight);
		sliderAttachment[i].reset(new juce::AudioProcessorValueTreeState::SliderAttachment(p.treeState, IDs[i], sliders[i]));
		addAndMakeVisible(sliders[i]);
	}
	
	//Add labels to sliders
	std::string sliderNames[] = { "Attack", "Decay", "Sustain", "Release" };
	for (int i = 0; i < sliderCount; i++) 
	{
		labels[i].setText(sliderNames[i], juce::NotificationType::dontSendNotification);
		labels[i].attachToComponent(&sliders[i], true);
		addAndMakeVisible(labels[i]);
	}
}

void EnvelopeSliders::resized()
{
	int insetY = 10;
	int leftPadding = 70;
	int rightPadding = 20;
	int sliderHeight = 36;

	auto area = getLocalBounds();
	area.reduce(0, insetY);
	area.removeFromLeft(leftPadding);
	area.removeFromRight(rightPadding);
	for (int i = 0; i < sliderCount; i++)
	{ 
		sliders[i].setBounds(area.removeFromTop(sliderHeight));
	}
}



