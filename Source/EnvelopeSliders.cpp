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
	for (int i = 0; i < 4; i++) {
		sliders[i].setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		sliders[i].setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
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

	std::string sliderNames[] = { "Attack", "Decay", "Sustain", "Release" };
	for (int i = 0; i < 4; i++) {
		labels[i].setText(sliderNames[i], juce::NotificationType::dontSendNotification);
		labels[i].setJustificationType(juce::Justification::centredTop);
		addAndMakeVisible(labels[i]);
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

	juce::FlexBox sliderBox;
	sliderBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	sliderBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
	sliderBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < 4; i++) {
		sliderBox.items.add(juce::FlexItem(sliders[i]).withMinWidth(50).withMinHeight(200));
	}
	sliderBox.performLayout(area.removeFromTop(200));

	juce::FlexBox labelBox;
	labelBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	labelBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
	labelBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < 4; i++) {
		labelBox.items.add(juce::FlexItem(labels[i]).withMinWidth(50).withMinHeight(20));
	}
	labelBox.performLayout(area.removeFromTop(20));
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
	juce::Logger::writeToLog(labels[sliderIndex].getText());
	juce::Logger::writeToLog(std::to_string(sliders[sliderIndex].getValue()));
}



