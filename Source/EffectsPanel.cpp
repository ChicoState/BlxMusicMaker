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
    BLXLookAndFeel blx;
    panelLabel.setText("Effects", juce::NotificationType::dontSendNotification);
    panelLabel.setColour(juce::Label::backgroundColourId, blx.getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::menuBackground));
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

    area.reduce(10, 18);
    arpegEffect->setBounds(area.removeFromTop(arpegEffect->getNeededHeight()));

    area.removeFromTop(10);
    tremEffect->setBounds(area.removeFromTop(tremEffect->getNeededHeight()));

    area.removeFromTop(10);
    vibEffect->setBounds(area.removeFromTop(vibEffect->getNeededHeight()));

    area.removeFromTop(10);
    noteEffect->setBounds(area.removeFromTop(noteEffect->getNeededHeight()));
}
