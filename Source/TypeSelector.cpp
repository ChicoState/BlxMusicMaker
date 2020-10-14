/*
  ==============================================================================

    TypeSelector.cpp
    Created: 13 Oct 2020 9:28:10pm
    Author:  alext

  ==============================================================================
*/

#include "TypeSelector.h"

TypeSelector::TypeSelector()
{
	std::string buttonNames[] = { "Pulse", "Triangle", "Saw", "Sine", "Noise" };
	buttons = new juce::TextButton[5];
	for (int i = 0; i < 5; i++) {
		buttons[i].setButtonText(buttonNames[i]);
		buttons[i].setRadioGroupId(radioId);
		buttons[i].setClickingTogglesState(true);
		buttons[i].onClick = [this, i] { updateToggleState(&buttons[i]); };
		addAndMakeVisible(buttons[i]);
	}
}

TypeSelector::~TypeSelector()
{
	delete[] buttons;
}

void TypeSelector::paint(juce::Graphics& g)
{
}

void TypeSelector::resized()
{
	auto area = getLocalBounds();

	juce::FlexBox topFlexBox;
	topFlexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	topFlexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
	topFlexBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < 3; i++) {
		topFlexBox.items.add(juce::FlexItem(buttons[i]).withMinWidth(100).withMinHeight(100).withMargin(5));
	}
	topFlexBox.performLayout(area.removeFromTop(100));

	area.removeFromTop(10);
	juce::FlexBox bottomFlexBox;
	bottomFlexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	bottomFlexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
	bottomFlexBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 3; i < 5; i++) {
		bottomFlexBox.items.add(juce::FlexItem(buttons[i]).withMinWidth(100).withMinHeight(100).withMargin(5));
	}
	bottomFlexBox.performLayout(area.removeFromTop(100));
}

void TypeSelector::updateToggleState(juce::TextButton* button)
{
	if (button->getToggleState())
	{
		juce::Logger::writeToLog(button->getButtonText());
	}
}
