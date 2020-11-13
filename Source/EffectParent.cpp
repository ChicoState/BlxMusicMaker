/*
  ==============================================================================

    EffectParent.cpp
    Created: 29 Oct 2020 1:20:49pm
    Author: kyle 

  ==============================================================================
*/

#include "EffectParent.h"

EffectParent::EffectParent(std::string effectName)
{
    toggle.setButtonText(effectName);
	//toggle.onClick = [this] { onEffectToggle(&toggle); };
    addAndMakeVisible(toggle);
    toggleAttachment.reset
    (
        new juce::AudioProcessorValueTreeState::ButtonAttachment(*StateManager::get().treeState, effectName, toggle)
    );
}

EffectParent::~EffectParent()
{
    //delete speedComp;
    //delete sliderComp;
}

int EffectParent::getNeededHeight()
{
    int childCount = getNumChildComponents();
    return (childCount * 24) + 6 + 4;
}

void EffectParent::addSliderComponent(std::string text, int minValue, int maxValue)
{
    sliderComp = new SliderComponent(text, minValue, maxValue);
    //sliderComp->slider.onValueChange = [this, sliderComp] { onSliderMove(&sliderComp->slider); };
    addAndMakeVisible(sliderComp);
}

void EffectParent::addSpeedComponent()
{
    //speedComp = new SpeedComponent();
    /*
    for (int i = 0; i < 4; i++) {
        speedComp->buttons[i].onClick = [this, i] { onSpeedToggle(static_cast<SpeedComponent::SpeedValue>(i)); };
    }
    */
    addAndMakeVisible(speedComp);
}

void EffectParent::paint(juce::Graphics& g)
{
    int childCount = getNumChildComponents();
    auto area = getLocalBounds();
    area.removeFromTop((childCount * 24) + 6);
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
    }
}