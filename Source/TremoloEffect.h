/*
  ==============================================================================

    TremoloEffect.h
    Created: 29 Oct 2020 7:41:41pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EffectParent.h" 

class TremoloEffect : public EffectParent
{
public:

    TremoloEffect(juce::AudioProcessorValueTreeState& treeState) : EffectParent::EffectParent("Tremolo")
    {
        //EffectParent::addSpeedComponent();
        EffectParent::addSliderComponent("Depth", -12, 12);
    };
    void onEffectToggle(juce::ToggleButton*) override;
    void onSliderMove(juce::Slider*) override;
    void onSpeedToggle(SpeedComponent::SpeedValue) override;

};
