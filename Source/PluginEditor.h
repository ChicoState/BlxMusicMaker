/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BLXLookAndFeel.h"
#include "PresetsBar.h"
#include "WavePanel.h"
#include "EnvelopePanel.h"
#include "EffectsPanel.h"

class BlxMusicMakerAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    BlxMusicMakerAudioProcessorEditor (BlxMusicMakerAudioProcessor&);
    ~BlxMusicMakerAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    BlxMusicMakerAudioProcessor& audioProcessor;

    //Main GUI Classes
    BLXLookAndFeel blxLookAndFeel;
    PresetsBar presetsBar;
    WavePanel wavePanel;
    EnvelopePanel envelopePanel;
    EffectsPanel *effectsPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlxMusicMakerAudioProcessorEditor)
};









