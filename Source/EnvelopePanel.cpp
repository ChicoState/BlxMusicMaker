/*
  ==============================================================================

    EnvelopePanel.cpp
    Created: 20 Oct 2020 8:03:47pm
    Author: kyle 

  ==============================================================================
*/

#include "EnvelopePanel.h"

EnvelopePanel::EnvelopePanel(BlxMusicMakerAudioProcessor& p)
{
    BLXLookAndFeel blx;
    panelLabel.setText("Envelopes", juce::NotificationType::dontSendNotification);
    panelLabel.setColour(juce::Label::backgroundColourId, blx.getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::menuBackground));
    addAndMakeVisible(panelLabel);

    sliders = new EnvelopeSliders(p);
    addAndMakeVisible(sliders);
}

EnvelopePanel::~EnvelopePanel()
{
    delete sliders;
}

void EnvelopePanel::paint(juce::Graphics& g)
{
    BLXLookAndFeel blx;
    g.setColour(blx.getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::windowBackground));
    g.fillRect(BLXLookAndFeel::getEnvelopeInsetArea(getLocalBounds()));
}

void EnvelopePanel::resized()
{
    auto area = BLXLookAndFeel::getEnvelopeInsetArea(getLocalBounds());
    auto labelArea = area.removeFromTop(BLXLookAndFeel::getPanelLabelHeight());
    panelLabel.setBounds(labelArea);
    panelLabel.setJustificationType(juce::Justification::centred);
    sliders->setBounds(area);
}
