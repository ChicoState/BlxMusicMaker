/*
  ==============================================================================

    EffectParent.h
    Created: 29 Oct 2020 1:20:49pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SliderComponent.h" 
#include "SpeedComponent.h" 
#include "BLXLookAndFeel.h"
#include "StateManager.h"

class EffectParent : public juce::Component
{
public:
    
    EffectParent(std::string);
    ~EffectParent();
    void paint(juce::Graphics&) override;
    void resized() override;
    int getNeededHeight();

    //Add Components
    void addSliderComponent(std::string, int, int);
    void addSpeedComponent();

    //Callbacks
    virtual void onEffectToggle(juce::ToggleButton*) = 0;
    virtual void onSliderMove(juce::Slider*) {};
    virtual void onSpeedToggle(SpeedComponent::SpeedValue) {};

private:

    juce::ToggleButton toggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleAttachment;
    SpeedComponent* speedComp;
    SliderComponent* sliderComp;

};
