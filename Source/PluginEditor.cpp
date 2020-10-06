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
    setSize (400, 300);

    // setup default slider stuff here
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    attackTree = new juce::AudioProcessorValueTreeState::SliderAttachment(
        audioProcessor.tree, "attack", attackSlider);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.1f);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);
    releaseTree = new juce::AudioProcessorValueTreeState::SliderAttachment(
        audioProcessor.tree, "release", releaseSlider);

}

BlxMusicMakerAudioProcessorEditor::~BlxMusicMakerAudioProcessorEditor()
{
}

//==============================================================================
void BlxMusicMakerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    /*
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    */
}

void BlxMusicMakerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // update the bounds of the sliders here
    attackSlider.setBounds(10, 10, 40, 100);
    releaseSlider.setBounds(50, 10, 40, 100);
}

void BlxMusicMakerAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // adjust the slider that was passed in's values 
    if (slider == &attackSlider)
        audioProcessor.attackTime = attackSlider.getValue();
    else if (slider == &releaseSlider)
        audioProcessor.releaseTime = releaseSlider.getValue();
}
















