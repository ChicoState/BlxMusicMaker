/*
  ==============================================================================

    VibratoEffect.cpp
    Created: 29 Oct 2020 7:42:03pm
    Author: kyle 

  ==============================================================================
*/

#include "VibratoEffect.h"

void VibratoEffect::onEffectToggle(juce::ToggleButton *toggle)
{
    if (toggle->getToggleState())
    {
        //Place code for on
        return;
    }
    //Place code for off
}

void VibratoEffect::onSliderMove(juce::Slider* slider)
{

}

void VibratoEffect::onSpeedToggle(SpeedComponent::SpeedValue speedValue)
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
