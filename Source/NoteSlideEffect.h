/*
  ==============================================================================

    NoteSlideEffect.h
    Created: 29 Oct 2020 7:42:16pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EffectParent.h" 

class NoteSlideEffect : public EffectParent
{
public:

    NoteSlideEffect() : EffectParent::EffectParent("Note Slide")
    {
        EffectParent::addSpeedComponent("Speed", "NoteSlideSpeed");
        EffectParent::addSliderComponent("Half-Steps", "NoteSlideDepth");
    };

};
