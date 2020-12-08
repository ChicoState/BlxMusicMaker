/*
  ==============================================================================

    EffectsPanel.cpp
    Created: 20 Oct 2020 8:04:06pm
    Author: kyle 

  ==============================================================================
*/

#include "EffectsPanel.h"

EffectsPanel::EffectsPanel(BlxMusicMakerAudioProcessor& p)
{
    panelLabel.setText("Effects", juce::NotificationType::dontSendNotification);
    panelLabel.setColour(juce::Label::backgroundColourId, 
        BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::menuBackground));
    addAndMakeVisible(panelLabel);

    arpegEffect = new ArpeggiatorEffect(p);
    addAndMakeVisible(arpegEffect);

    tremEffect = new TremoloEffect(p);
    addAndMakeVisible(tremEffect);

    vibEffect = new VibratoEffect(p);
    addAndMakeVisible(vibEffect);

    noteEffect = new NoteSlideEffect(p);
    addAndMakeVisible(noteEffect);
}

EffectsPanel::~EffectsPanel()
{
    delete arpegEffect;
    delete tremEffect;
    delete vibEffect;
    delete noteEffect;
}

void EffectsPanel::paint(juce::Graphics& g)
{
    g.setColour(BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::windowBackground));
    g.fillRect(getInsetArea(getLocalBounds()));
}

void EffectsPanel::resized()
{
    int panelLabelHeight = 25;
    int insetWidth = 15;
    int insetHeight = 10;
    int componentSpacing = 10;

    auto area = getInsetArea(getLocalBounds());
    auto labelArea = area.removeFromTop(panelLabelHeight);
    panelLabel.setBounds(labelArea);
    panelLabel.setJustificationType(juce::Justification::centred);

    area.reduce(insetWidth, insetHeight);
    arpegEffect->setBounds(area.removeFromTop(arpegEffect->getNeededHeight()));

    area.removeFromTop(componentSpacing);
    tremEffect->setBounds(area.removeFromTop(tremEffect->getNeededHeight()));

    area.removeFromTop(componentSpacing);
    vibEffect->setBounds(area.removeFromTop(vibEffect->getNeededHeight()));

    area.removeFromTop(componentSpacing);
    noteEffect->setBounds(area.removeFromTop(noteEffect->getNeededHeight()));
}

juce::Rectangle<int> EffectsPanel::getInsetArea(juce::Rectangle<int> area)
{
    int panelInset = 4;
    area.removeFromTop(panelInset);
    area.removeFromLeft(panelInset / 2);
    area.removeFromRight(panelInset);
    area.removeFromBottom(panelInset);
    return area;
}
