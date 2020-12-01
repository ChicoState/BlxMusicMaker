/*
  ==============================================================================

    EffectParent.cpp
    Created: 29 Oct 2020 1:20:49pm
    Author: kyle 

  ==============================================================================
*/

#include "EffectParent.h"

EffectParent::EffectParent(std::string effectName, BlxMusicMakerAudioProcessor& p)
{
    toggle.setButtonText(effectName);
    addAndMakeVisible(toggle);
    toggleAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(p.treeState, effectName, toggle));
}

EffectParent::~EffectParent()
{
    for(int i = 0; i < (int)components.size(); i++)
    {
        delete components[i];
    }
}

int EffectParent::getNeededHeight()
{
    int childCount = getNumChildComponents();
    return (childCount * 26) + 6 + 4;
}

void EffectParent::addSliderComponent(std::string text, std::string stateID, BlxMusicMakerAudioProcessor& p)
{
    SliderComponent* sliderComp = new SliderComponent(text, stateID, p);
    addAndMakeVisible(sliderComp);
    components.push_back(sliderComp);
}

void EffectParent::addSpeedComponent(std::string text, std::string stateID, BlxMusicMakerAudioProcessor& p)
{
    SpeedComponent* speedComp = new SpeedComponent(text, stateID, p);
    addAndMakeVisible(speedComp);
    components.push_back(speedComp);
}

void EffectParent::paint(juce::Graphics& g)
{
    int childCount = getNumChildComponents();
    auto area = getLocalBounds();
    area.removeFromTop((childCount * 26) + 6);
    BLXLookAndFeel blx;
    g.setColour(blx.getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::outline));
    g.fillRect(area.removeFromTop(4));
}

void EffectParent::resized()
{
    auto area = getLocalBounds();
    int childCount = getNumChildComponents();
    for (int i = 0; i < childCount; i++) {
        if (i == 1) {
            area.removeFromLeft(35);
        }
        getChildComponent(i)->setBounds(area.removeFromTop(24));
        if (i != 0)
        {
            area.removeFromTop(2);
        }
    }
}
