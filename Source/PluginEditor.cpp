/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BlxMusicMakerAudioProcessorEditor::BlxMusicMakerAudioProcessorEditor (BlxMusicMakerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    menu = new Menu;
    instrumentWindow = new InstrumentWindow;
    addAndMakeVisible(menu);
    addAndMakeVisible(instrumentWindow);
    setSize(900, 600);
}

BlxMusicMakerAudioProcessorEditor::~BlxMusicMakerAudioProcessorEditor()
{
    delete menu;
    delete instrumentWindow;
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
    menu->setBounds(area.removeFromTop(menuBarHeight));
    instrumentWindow->setBounds(area);
}

void BlxMusicMakerAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    /*
    // adjust the slider that was passed in's values 
    if (slider == &attackSlider)
        audioProcessor.attackTime = attackSlider.getValue();
    else if (slider == &releaseSlider)
        audioProcessor.releaseTime = releaseSlider.getValue();
    */
}
















