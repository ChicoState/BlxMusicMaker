/*
  ==============================================================================

    TypeSelector.cpp
    Created: 13 Oct 2020 9:28:10pm
    Author: kyle 

  ==============================================================================
*/

#include "WaveSelector.h"

TypeSelector::TypeSelector()
{
	int radioID = BLXLookAndFeel::getNewRadioID();
	std::string buttonNames[] = { "Pulse25", "Pulse50", "Pulse75", "Triangle", "Saw", "Sine", "Noise" };
	for (int i = 0; i < 7; i++) {
		waveButtons[i].setButtonText(buttonNames[i]);
		waveButtons[i].setRadioGroupId(radioID);
		waveButtons[i].setClickingTogglesState(true);
		waveButtons[i].onClick = [this, i] { updateToggleState(i); };
		addAndMakeVisible(waveButtons[i]);
	}
	waveButtons[0].triggerClick();
}

TypeSelector::~TypeSelector()
{
}

void TypeSelector::paint(juce::Graphics& g)
{
}

void TypeSelector::resized()
{
	auto area = getLocalBounds();

	area.reduce(15, 10);

	juce::FlexBox topFlexBox;
	topFlexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	topFlexBox.justifyContent = juce::FlexBox::JustifyContent::center;
	topFlexBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < 4; i++) {
		topFlexBox.items.add(juce::FlexItem(waveButtons[i]).withMinWidth(80).withMinHeight(80).withMargin(5));
	}
	topFlexBox.performLayout(area.removeFromTop(100));

	area.removeFromTop(10);
	juce::FlexBox bottomFlexBox;
	bottomFlexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	bottomFlexBox.justifyContent = juce::FlexBox::JustifyContent::center;
	bottomFlexBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 4; i < 7; i++) {
		bottomFlexBox.items.add(juce::FlexItem(waveButtons[i]).withMinWidth(80).withMinHeight(80).withMargin(5));
	}
	bottomFlexBox.performLayout(area.removeFromTop(100));
}

void TypeSelector::updateToggleState(int buttonIndex)
{
	if (waveButtons[buttonIndex].getToggleState())
	{
		SynthVoice::currentWaveFlag = (SynthVoice::waveFlag)buttonIndex;
	}
}
