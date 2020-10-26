/*
  ==============================================================================

    EffectsPanel.cpp
    Created: 20 Oct 2020 8:04:06pm
    Author: kyle 

  ==============================================================================
*/

#include "EffectsPanel.h"

EffectsPanel::EffectsPanel()
{
    BLXLookAndFeel blx;
    panelLabel.setText("Effects", juce::NotificationType::dontSendNotification);
    panelLabel.setColour(juce::Label::backgroundColourId, blx.getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::menuBackground));
    addAndMakeVisible(panelLabel);
}

void EffectsPanel::paint(juce::Graphics& g)
{
    BLXLookAndFeel blx;
    g.setColour(blx.getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::windowBackground));
    g.fillRect(BLXLookAndFeel::getEffectsInsetArea(getLocalBounds()));
}

void EffectsPanel::resized()
{
    auto area = BLXLookAndFeel::getEffectsInsetArea(getLocalBounds());
    auto labelArea = area.removeFromTop(BLXLookAndFeel::getPanelLabelHeight());
    panelLabel.setBounds(labelArea);
    panelLabel.setJustificationType(juce::Justification::centred);
}
