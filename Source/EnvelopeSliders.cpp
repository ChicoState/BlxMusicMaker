/*
  ==============================================================================

    EnvelopeSliders.cpp
    Created: 13 Oct 2020 9:28:54pm
    Author:  alext

  ==============================================================================
*/

#include "EnvelopeSliders.h"

EnvelopeSliders::EnvelopeSliders()
{
	std::string IDs[4] = { "Attack", "Decay", "Sustain", "Release" };
	for (int i = 0; i < 4; i++) 
	{
		sliders[i].setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		sliders[i].setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, 50, 20);
		sliderAttachment[i].reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*StateManager::get().treeState, IDs[i], sliders[i]));
		addAndMakeVisible(sliders[i]);
	}
	
	//Add labels to sliders
	std::string sliderNames[] = { "Attack", "Decay", "Sustain", "Release" };
	for (int i = 0; i < 4; i++) 
	{
		addAndMakeVisible(labels[i]);
		labels[i].setText(sliderNames[i], juce::NotificationType::dontSendNotification);
		labels[i].attachToComponent(&sliders[i], true);
	}
}

EnvelopeSliders::~EnvelopeSliders()
{
}

void EnvelopeSliders::paint(juce::Graphics& g)
{
}

void EnvelopeSliders::resized()
{
	auto area = getLocalBounds();
	area.reduce(0, 10);
	area.removeFromLeft(70);
	area.removeFromRight(20);
	for (int i = 0; i < 4; i++)
	{ 
		sliders[i].setBounds(area.removeFromTop(36));
	}
}



