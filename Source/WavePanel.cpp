/*
  ==============================================================================

    WavePanel.cpp
    Created: 20 Oct 2020 7:34:09pm
    Author: kyle  

  ==============================================================================
*/

#include "WavePanel.h"

WavePanel::WavePanel()
{
    BLXLookAndFeel blx;
    panelLabel.setText("Waves", juce::NotificationType::dontSendNotification);
    panelLabel.setColour(juce::Label::backgroundColourId, blx.getCurrentColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::menuBackground));
    addAndMakeVisible(panelLabel);
    addAndMakeVisible(typeSelector);
}

void WavePanel::paint(juce::Graphics& g)
{
    BLXLookAndFeel blx;
    g.setColour(blx.getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::windowBackground));
    g.fillRect(BLXLookAndFeel::getWaveInsetArea(getLocalBounds()));
}

void WavePanel::resized()
{
    auto area = BLXLookAndFeel::getWaveInsetArea(getLocalBounds());
    auto labelArea = area.removeFromTop(BLXLookAndFeel::getPanelLabelHeight());
    panelLabel.setBounds(labelArea);
    panelLabel.setJustificationType(juce::Justification::centred);
    typeSelector.setBounds(area);
}
