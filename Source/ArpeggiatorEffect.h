/*
  ==============================================================================

    ArpeggiatorEffect.h
    Created: 28 Oct 2020 6:10:36pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EffectParent.h"
#include "StateManager.h"

class ArpeggiatorEffect : public EffectParent
{
public:

    ArpeggiatorEffect() : EffectParent("Arpeggiator") 
    {
        speedAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*StateManager::get().treeState, "ArpegSpeed", speedSlider));
        speedComp = new SpeedComponent();
        for (int i = 0; i < 4; i++) {
            speedComp->buttons[i].onClick = [this, i] { onSpeedToggle(static_cast<SpeedComponent::SpeedValue>(i)); };
        }
        EffectParent::addAndMakeVisible(speedComp);
    };
    ~ArpeggiatorEffect();
    void onSpeedToggle(SpeedComponent::SpeedValue);
    void onEffectToggle(juce::ToggleButton*) override;

private:

    SpeedComponent* speedComp;
    juce::Slider speedSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> speedAttachment;
};
