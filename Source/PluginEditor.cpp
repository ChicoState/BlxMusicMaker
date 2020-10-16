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
    addAndMakeVisible(menu);
    addAndMakeVisible(instrumentWindow);
    setSize(900, 600);
}

BlxMusicMakerAudioProcessorEditor::~BlxMusicMakerAudioProcessorEditor()
{
}

//==============================================================================
void BlxMusicMakerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setFont(juce::Font(16.0f));
    g.setColour(juce::Colours::white);
}

void BlxMusicMakerAudioProcessorEditor::resized()
{
    juce::LookAndFeel_V4 lookAndFeel;
    auto area = getLocalBounds();
    int menuBarHeight = lookAndFeel.getDefaultMenuBarHeight();
    menu.setBounds(area.removeFromTop(menuBarHeight));
    instrumentWindow.setBounds(area);
}















