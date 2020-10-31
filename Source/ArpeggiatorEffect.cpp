/*
  ==============================================================================

    ArpeggiatorEffect.cpp
    Created: 28 Oct 2020 6:10:36pm
    Author: kyle 

  ==============================================================================
*/

#include "ArpeggiatorEffect.h"

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
    switch (speedValue)
    {
    case SpeedComponent::SpeedValue::eighth: 

        break;
    case SpeedComponent::SpeedValue::quarter: 

        break;
    case SpeedComponent::SpeedValue::half: 

        break;
    case SpeedComponent::SpeedValue::whole: 

        break;
    }
}

