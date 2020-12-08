/*
  ==============================================================================

    TypeSelector.h
    Created: 13 Oct 2020 9:28:10pm
    Author:  alext

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthVoice.h"
#include "BLXLookAndFeel.h"
#include "PluginProcessor.h"
#include "SynthVoice.h"

class TypeSelector : public juce::Component
{
public:

    TypeSelector(BlxMusicMakerAudioProcessor&);
    void resized() override;

private:

    void onButtonSelect(int);
    void onValueChange();
    juce::Image getPressedImage(int);
    juce::Image getHighlightedImage(int);
    juce::Image getNotPressedImage(int);

    const int buttonCount = 7;
    juce::ImageButton waveButtons[7];
    juce::Label labels[7];
    juce::Slider slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;

};
