/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

//==============================================================================
BlxMusicMakerAudioProcessorEditor::BlxMusicMakerAudioProcessorEditor (BlxMusicMakerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor(p)
{
    blxLookAndFeel = new BLXLookAndFeel;
    juce::LookAndFeel::setDefaultLookAndFeel(blxLookAndFeel);
    addAndMakeVisible(presetsBar);
    addAndMakeVisible(wavePanel);
    addAndMakeVisible(envelopePanel);
    addAndMakeVisible(effectsPanel);
    setSize(900, 600);
}

BlxMusicMakerAudioProcessorEditor::~BlxMusicMakerAudioProcessorEditor()
{
    delete blxLookAndFeel;
}

//==============================================================================
void BlxMusicMakerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setFont(juce::Font(16.0f));
    g.setColour(juce::Colours::white);
}

void BlxMusicMakerAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    int menuBarHeight = getLookAndFeel().getDefaultMenuBarHeight();
    presetsBar.setBounds(area.removeFromTop(menuBarHeight));
    auto waveArea = area.removeFromLeft(area.getWidth() / 2);
    auto envelopeArea = waveArea.removeFromBottom(200);
    wavePanel.setBounds(waveArea);
    envelopePanel.setBounds(envelopeArea);
    effectsPanel.setBounds(area);
}
