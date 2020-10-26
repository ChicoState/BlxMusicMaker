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
	for (int i = 0; i < 4; i++) 
	{
		sliders[i].setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
		sliders[i].setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxRight, false, 50, 20);
		sliders[i].onValueChange = [this, i] { sliderValueChanged(i); };
		addAndMakeVisible(sliders[i]);
	}
	
	// Attack value and range
	sliders[0].setValue(BlxMusicMakerAudioProcessor::attackTime);
	sliders[0].setRange(BlxMusicMakerAudioProcessor::attackTime, 5000.0f);

	// Decay value and range
	sliders[1].setValue(BlxMusicMakerAudioProcessor::decayTime);
	sliders[1].setRange(BlxMusicMakerAudioProcessor::decayTime, 5000.0f);

	// Sustain value and range
	sliders[2].setValue(BlxMusicMakerAudioProcessor::sustainTime);
	sliders[2].setRange(BlxMusicMakerAudioProcessor::sustainTime, 1.0f);

	// Release value and range
	sliders[3].setValue(BlxMusicMakerAudioProcessor::releaseTime);
	sliders[3].setRange(BlxMusicMakerAudioProcessor::releaseTime, 5000.0f);

	//Set slider decimal points, needs to be assigned after range
	for (int i = 0; i < 4; i++) 
	{
		if (i == 2) 
		{
			sliders[i].setNumDecimalPlacesToDisplay(2);
		}
		else
		{
			sliders[i].setNumDecimalPlacesToDisplay(0);
		}
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
	//juce::Logger::writeToLog(to_string(sliders[0].getHeight()));
}

void EnvelopeSliders::sliderValueChanged(int sliderIndex)
{
	// connection btw GUI and processor
	switch (sliderIndex)
	{
	case 0:
		BlxMusicMakerAudioProcessor::attackTime = sliders[0].getValue();
		break;
	case 1:
		BlxMusicMakerAudioProcessor::decayTime = sliders[1].getValue();
		break;
	case 2:
		BlxMusicMakerAudioProcessor::sustainTime = sliders[2].getValue();
		break;
	case 3:
		BlxMusicMakerAudioProcessor::releaseTime = sliders[3].getValue();
		break;
	}
	//juce::Logger::writeToLog(labels[sliderIndex].getText());
	//juce::Logger::writeToLog(std::to_string(sliders[sliderIndex].getValue()));
}



