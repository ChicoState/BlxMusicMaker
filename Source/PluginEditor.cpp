/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"


//==============================================================================
BlxMusicMakerAudioProcessorEditor::BlxMusicMakerAudioProcessorEditor(BlxMusicMakerAudioProcessor& p)
                                                                    : AudioProcessorEditor(&p), audioProcessor(p)
{
    juce::LookAndFeel::setDefaultLookAndFeel(&blxLookAndFeel);
    addAndMakeVisible(wavePanel);
    addAndMakeVisible(envelopePanel);
    addAndMakeVisible(effectsPanel);
    setSize(800, 500);
}

BlxMusicMakerAudioProcessorEditor::~BlxMusicMakerAudioProcessorEditor()
{
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
    auto waveArea = area.removeFromLeft(area.getWidth() / 2);
    auto envelopeArea = waveArea.removeFromBottom(200);
    wavePanel.setBounds(waveArea);
    envelopePanel.setBounds(envelopeArea);
    effectsPanel.setBounds(area);
}

