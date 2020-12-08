/*
  ==============================================================================

    TypeSelector.cpp
    Created: 13 Oct 2020 9:28:10pm
    Author: kyle 

  ==============================================================================
*/

#include "WaveSelector.h"

TypeSelector::TypeSelector(BlxMusicMakerAudioProcessor& p)
{
	int radioID = 101;
	std::string buttonNames[] = { "Pulse25", "Pulse50", "Pulse75", "Triangle", "Saw", "Sine", "Noise" };
	for (int i = 0; i < buttonCount; i++) 
	{
		waveButtons[i].setImages
		(
			false, true, true, 
			getNotPressedImage(i), 1.0f, Colours::transparentWhite, 
			getHighlightedImage(i), 1.0f, Colours::transparentWhite, 
			getPressedImage(i), 1.0f, Colours::transparentWhite
		);
		waveButtons[i].setRadioGroupId(radioID);
		waveButtons[i].setClickingTogglesState(true);
		waveButtons[i].onClick = [this, i] { onButtonSelect(i); };
		addAndMakeVisible(waveButtons[i]);

		labels[i].setText(buttonNames[i], juce::NotificationType::dontSendNotification);
		labels[i].setJustificationType(juce::Justification::centred);
		addAndMakeVisible(labels[i]);
	}
	waveButtons[0].triggerClick();
	slider.onValueChange = [this] { onValueChange(); };
    sliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(p.treeState, "Wave", slider));
}

void TypeSelector::resized()
{
	int inset = 15;
	int topRowCount = 4;
	int buttonFlexSize = 85;
	int labelFlexSize = 30;
	int spaceBetweenRows = 10;
	int buttonSize = 80;
	int labelHeight = 30;
	int margin = 5;

	auto area = getLocalBounds();
	area.reduce(inset, inset);

	juce::FlexBox topButtonFlex;
	topButtonFlex.flexWrap = juce::FlexBox::Wrap::noWrap;
	topButtonFlex.justifyContent = juce::FlexBox::JustifyContent::center;
	topButtonFlex.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < topRowCount; i++) 
	{
		topButtonFlex.items.add(juce::FlexItem(waveButtons[i]).withMinWidth(buttonSize).withMinHeight(buttonSize).withMargin(margin));
	}
	topButtonFlex.performLayout(area.removeFromTop(buttonFlexSize));

	juce::FlexBox topLabelFlex;
	topLabelFlex.flexWrap = juce::FlexBox::Wrap::noWrap;
	topLabelFlex.justifyContent = juce::FlexBox::JustifyContent::center;
	topLabelFlex.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < topRowCount; i++) 
	{
		topLabelFlex.items.add(juce::FlexItem(labels[i]).withMinWidth(buttonSize).withMinHeight(labelHeight).withMargin(margin));
	}
	topLabelFlex.performLayout(area.removeFromTop(labelFlexSize));

	area.removeFromTop(spaceBetweenRows);

	juce::FlexBox bottomFlexBox;
	bottomFlexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	bottomFlexBox.justifyContent = juce::FlexBox::JustifyContent::center;
	bottomFlexBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = topRowCount; i < buttonCount; i++) 
	{
		bottomFlexBox.items.add(juce::FlexItem(waveButtons[i]).withMinWidth(buttonSize).withMinHeight(buttonSize).withMargin(margin));
	}
	bottomFlexBox.performLayout(area.removeFromTop(buttonFlexSize));

	juce::FlexBox bottomLabelFlex;
	bottomLabelFlex.flexWrap = juce::FlexBox::Wrap::noWrap;
	bottomLabelFlex.justifyContent = juce::FlexBox::JustifyContent::center;
	bottomLabelFlex.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = topRowCount; i < buttonCount; i++) 
	{
		bottomLabelFlex.items.add(juce::FlexItem(labels[i]).withMinWidth(buttonSize).withMinHeight(labelHeight).withMargin(margin));
	}
	bottomLabelFlex.performLayout(area.removeFromTop(labelFlexSize));
}

void TypeSelector::onButtonSelect(int index)
{
	slider.setValue(index);
}

void TypeSelector::onValueChange()
{
	waveButtons[(int)slider.getValue()].triggerClick();
}

juce::Image TypeSelector::getPressedImage(int i)
{
	SynthVoice::waveFlag waveFlag = (SynthVoice::waveFlag)i;
	switch (waveFlag)
	{
	case SynthVoice::waveFlag::Pulse25:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse25P_png, BinaryData::Pulse25P_pngSize);
	case SynthVoice::waveFlag::Pulse50:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse50P_png, BinaryData::Pulse50P_pngSize);
	case SynthVoice::waveFlag::Pulse75:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse75P_png, BinaryData::Pulse75P_pngSize);
	case SynthVoice::waveFlag::Triangle:
		return juce::ImageCache::getFromMemory(BinaryData::TriangleP_png, BinaryData::TriangleP_pngSize);
	case SynthVoice::waveFlag::Saw:
		return juce::ImageCache::getFromMemory(BinaryData::SawP_png, BinaryData::SawP_pngSize);
	case SynthVoice::waveFlag::Sine:
		return juce::ImageCache::getFromMemory(BinaryData::SineP_png, BinaryData::SineP_pngSize);
	case SynthVoice::waveFlag::Noise:
		return juce::ImageCache::getFromMemory(BinaryData::NoiseP_png, BinaryData::NoiseP_pngSize);
	}
}

juce::Image TypeSelector::getHighlightedImage(int i)
{
	SynthVoice::waveFlag waveFlag = (SynthVoice::waveFlag)i;
	switch (waveFlag)
	{
	case SynthVoice::waveFlag::Pulse25:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse25H_png, BinaryData::Pulse25H_pngSize);
	case SynthVoice::waveFlag::Pulse50:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse50H_png, BinaryData::Pulse50H_pngSize);
	case SynthVoice::waveFlag::Pulse75:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse75H_png, BinaryData::Pulse75H_pngSize);
	case SynthVoice::waveFlag::Triangle:
		return juce::ImageCache::getFromMemory(BinaryData::TriangleH_png, BinaryData::TriangleH_pngSize);
	case SynthVoice::waveFlag::Saw:
		return juce::ImageCache::getFromMemory(BinaryData::SawH_png, BinaryData::SawH_pngSize);
	case SynthVoice::waveFlag::Sine:
		return juce::ImageCache::getFromMemory(BinaryData::SineH_png, BinaryData::SineH_pngSize);
	case SynthVoice::waveFlag::Noise:
		return juce::ImageCache::getFromMemory(BinaryData::NoiseH_png, BinaryData::NoiseH_pngSize);
	}
}

juce::Image TypeSelector::getNotPressedImage(int i)
{
	SynthVoice::waveFlag waveFlag = (SynthVoice::waveFlag)i;
	switch (waveFlag)
	{
	case SynthVoice::waveFlag::Pulse25:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse25NP_png, BinaryData::Pulse25NP_pngSize);
	case SynthVoice::waveFlag::Pulse50:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse50NP_png, BinaryData::Pulse50NP_pngSize);
	case SynthVoice::waveFlag::Pulse75:
		return juce::ImageCache::getFromMemory(BinaryData::Pulse75NP_png, BinaryData::Pulse75NP_pngSize);
	case SynthVoice::waveFlag::Triangle:
		return juce::ImageCache::getFromMemory(BinaryData::TriangleNP_png, BinaryData::TriangleNP_pngSize);
	case SynthVoice::waveFlag::Saw:
		return juce::ImageCache::getFromMemory(BinaryData::SawNP_png, BinaryData::SawNP_pngSize);
	case SynthVoice::waveFlag::Sine:
		return juce::ImageCache::getFromMemory(BinaryData::SineNP_png, BinaryData::SineNP_pngSize);
	case SynthVoice::waveFlag::Noise:
		return juce::ImageCache::getFromMemory(BinaryData::NoiseNP_png, BinaryData::NoiseNP_pngSize);
	}
}
