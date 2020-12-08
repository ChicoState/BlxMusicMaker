/*
  ==============================================================================

    EffectParent.cpp
    Created: 29 Oct 2020 1:20:49pm
    Author: kyle 

  ==============================================================================
*/

#include "EffectParent.h"

EffectParent::EffectParent(std::string effectName, BlxMusicMakerAudioProcessor &p, bool isLastComponent)
{
    isLast = isLastComponent;
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
    return (childCount * componentHeight) + spaceAfterLastCopmonent + dividerHeight;
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
    if (isLast) return;
    int childCount = getNumChildComponents();
    auto area = getLocalBounds();
    area.removeFromTop((childCount * componentHeight) + spaceAfterLastCopmonent);
    g.setColour(BLXLookAndFeel().getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::outline));
    g.fillRect(area.removeFromTop(dividerHeight));
}

void EffectParent::resized()
{
    auto area = getLocalBounds();
    int childCount = getNumChildComponents();
    for (int i = 0; i < childCount; i++) {
        if (i == 1) 
        {
            int tabWidth = 35;
            area.removeFromLeft(tabWidth);
        }
        getChildComponent(i)->setBounds(area.removeFromTop(componentHeight));
    }
}
