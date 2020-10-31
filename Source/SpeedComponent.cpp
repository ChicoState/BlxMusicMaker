/*
  ==============================================================================

    SpeedComponent.cpp
    Created: 28 Oct 2020 2:31:19pm
    Author: kyle 

  ==============================================================================
*/

#include "SpeedComponent.h"

SpeedComponent::SpeedComponent()
{
    int radioID = BLXLookAndFeel::getNewRadioID();
    std::string speedTexts[] = { "1/8", "1/4", "1/2", "1" };
    for (int i = 0; i < 4; i++) {
        buttons[i].setButtonText(speedTexts[i]);
        buttons[i].setClickingTogglesState(true);
        buttons[i].setRadioGroupId(radioID);
        addAndMakeVisible(buttons[i]);
    }

    buttons[0].setToggleState(true, juce::NotificationType::dontSendNotification);

    label.setText("Speed", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(label);

}

void SpeedComponent::paint(juce::Graphics&)
{
}

void SpeedComponent::resized()
{
    auto area = getLocalBounds();
    label.setBounds(area.removeFromLeft(60));

    juce::FlexBox flexBox;
    flexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    flexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    flexBox.alignContent = juce::FlexBox::AlignContent::center;
    for (int i = 0; i < 4; i++) {
        flexBox.items.add(juce::FlexItem(buttons[i]).withMinWidth(50).withMinHeight(20).withMargin(5));
    }
    flexBox.performLayout(area);
}
