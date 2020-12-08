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

    NoteSlideEffect(BlxMusicMakerAudioProcessor& p) : EffectParent::EffectParent("Note Slide", p, true)
    {
        EffectParent::addSpeedComponent("Speed", "NoteSlideSpeed", p);
        EffectParent::addSliderComponent("Half-Steps", "NoteSlideDepth", p);
    };

};
