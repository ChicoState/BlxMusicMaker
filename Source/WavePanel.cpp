/*
  ==============================================================================

    WavePanel.cpp
    Created: 20 Oct 2020 7:34:09pm
    Author: kyle  

  ==============================================================================
*/

#include "WavePanel.h"

WavePanel::WavePanel(BlxMusicMakerAudioProcessor& p)
{
    panelLabel.setText("Waves", juce::NotificationType::dontSendNotification);
    panelLabel.setColour(juce::Label::backgroundColourId, 
        BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::menuBackground));
    addAndMakeVisible(panelLabel);

    typeSelector = new TypeSelector(p);
    addAndMakeVisible(typeSelector);
}

WavePanel::~WavePanel()
{
    delete typeSelector;
}

void WavePanel::paint(juce::Graphics& g)
{
    g.setColour(BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::windowBackground));
    g.fillRect(getInsetArea(getLocalBounds()));
}

void WavePanel::resized()
{
    int panelLabelHeight = 25;
    auto area = getInsetArea(getLocalBounds());
    auto labelArea = area.removeFromTop(panelLabelHeight);
    panelLabel.setBounds(labelArea);
    panelLabel.setJustificationType(juce::Justification::centred);
    typeSelector->setBounds(area);
}

juce::Rectangle<int> WavePanel::getInsetArea(juce::Rectangle<int> area)
{
    int panelInset = 4;
    area.removeFromTop(panelInset);
    area.removeFromLeft(panelInset);
    area.removeFromRight(panelInset / 2);
    area.removeFromBottom(panelInset / 2);
    return area;
}
