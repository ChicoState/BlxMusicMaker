/*
  ==============================================================================

    NoteSlideEffect.h
    Created: 29 Oct 2020 7:42:16pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EffectParent.h" 

class NoteSlideEffect : public EffectParent
{
public:

    NoteSlideEffect(juce::AudioProcessorValueTreeState& treeState) : EffectParent::EffectParent("Note Slide")
    {
        //EffectParent::addSpeedComponent();
        EffectParent::addSliderComponent("Half-Steps", -12, 12);
    };
    void onEffectToggle(juce::ToggleButton*) override;
    void onSliderMove(juce::Slider*) override;
    void onSpeedToggle(SpeedComponent::SpeedValue) override;

};
