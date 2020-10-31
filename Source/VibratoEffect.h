/*
  ==============================================================================

    VibratoEffect.h
    Created: 29 Oct 2020 7:42:03pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EffectParent.h" 

class VibratoEffect : public EffectParent  
{
public:

    VibratoEffect() : EffectParent::EffectParent("Vibrato") 
    {
        EffectParent::addSpeedComponent();
        EffectParent::addSliderComponent("Depth", -12, 12);
    };
    void onEffectToggle(juce::ToggleButton*) override;
    void onSliderMove(juce::Slider*) override;
    void onSpeedToggle(SpeedComponent::SpeedValue) override;

};

