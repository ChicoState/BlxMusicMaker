/*
  ==============================================================================

    TremoloEffect.cpp
    Created: 29 Oct 2020 7:41:41pm
    Author:  b

  ==============================================================================
*/

#include "TremoloEffect.h"

void TremoloEffect::onEffectToggle(juce::ToggleButton *toggle)
{
    if (toggle->getToggleState())
    {
        //Place code for on
        return;
    }
    //Place code for off
}

void TremoloEffect::onSliderMove(juce::Slider* slider)
{

}

void TremoloEffect::onSpeedToggle(SpeedComponent::SpeedValue speedValue)
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
