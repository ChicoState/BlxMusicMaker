/*
  ==============================================================================

    EffectParent.h
    Created: 29 Oct 2020 1:20:49pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <vector>
#include <JuceHeader.h>
#include "SliderComponent.h" 
#include "SpeedComponent.h" 
#include "BLXLookAndFeel.h"

class EffectParent : public juce::Component
{
public:
    
    EffectParent(std::string, BlxMusicMakerAudioProcessor&, bool isLastComponent = false);
    ~EffectParent();
    void paint(juce::Graphics&) override;
    void resized() override;
    int getNeededHeight();

    //Add Components
    void addSliderComponent(std::string, std::string, BlxMusicMakerAudioProcessor&);
    void addSpeedComponent(std::string, std::string, BlxMusicMakerAudioProcessor&);

private:

    const int componentHeight = 33;
    const int spaceAfterLastCopmonent = 12;
    const int dividerHeight = 4;
    juce::ToggleButton toggle;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> toggleAttachment;
    std::vector<juce::Component*> components;
    bool isLast;

};
