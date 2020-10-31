/*
  ==============================================================================

    NoteSlideEffect.cpp
    Created: 29 Oct 2020 7:42:16pm
    Author: kyle 

  ==============================================================================
*/

#include "NoteSlideEffect.h"

void NoteSlideEffect::onEffectToggle(juce::ToggleButton *toggle)
{
    if (toggle->getToggleState())
    {
        //Place code for on
        return;
    }
    //Place code for off
}

void NoteSlideEffect::onSliderMove(juce::Slider* slider)
{
}

void NoteSlideEffect::onSpeedToggle(SpeedComponent::SpeedValue speedValue)
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
