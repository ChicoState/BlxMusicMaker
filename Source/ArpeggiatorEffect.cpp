/*
  ==============================================================================

    ArpeggiatorEffect.cpp
    Created: 28 Oct 2020 6:10:36pm
    Author: kyle 

  ==============================================================================
*/

#include "ArpeggiatorEffect.h"

ArpeggiatorEffect::~ArpeggiatorEffect()
{
    delete speedComp;
}

void ArpeggiatorEffect::onEffectToggle(juce::ToggleButton *toggle)
{
    if (toggle->getToggleState())
    {
        //Place code for on
        return;
    }
    //Place code for off
}


void ArpeggiatorEffect::onSpeedToggle(SpeedComponent::SpeedValue speedValue)
{
    speedSlider.setValue((int)speedValue);
}

