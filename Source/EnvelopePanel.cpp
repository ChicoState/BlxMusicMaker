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
    panelLabel.setText("Envelopes", juce::NotificationType::dontSendNotification);
    panelLabel.setColour(juce::Label::backgroundColourId, 
        BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::menuBackground));
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
    g.setColour(BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::windowBackground));
    g.fillRect(getInsetArea(getLocalBounds()));
}

void EnvelopePanel::resized()
{
    int panelLabelHeight = 25;
    auto area = getInsetArea(getLocalBounds());
    auto labelArea = area.removeFromTop(panelLabelHeight);
    panelLabel.setBounds(labelArea);
    panelLabel.setJustificationType(juce::Justification::centred);
    sliders->setBounds(area);
}

juce::Rectangle<int> EnvelopePanel::getInsetArea(juce::Rectangle<int> area)
{
    int panelInset = 4;
    area.removeFromTop(panelInset / 2);
    area.removeFromLeft(panelInset);
    area.removeFromRight(panelInset / 2);
    area.removeFromBottom(panelInset);
    return area;
}

