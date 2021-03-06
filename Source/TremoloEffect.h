/*
  ==============================================================================

    TremoloEffect.h
    Created: 29 Oct 2020 7:41:41pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EffectParent.h" 

class TremoloEffect : public EffectParent
{
public:

    TremoloEffect(BlxMusicMakerAudioProcessor& p) : EffectParent::EffectParent("Tremolo", p)
    {
        EffectParent::addSpeedComponent("Speed", "TremoloSpeed", p);
        EffectParent::addSliderComponent("Depth", "TremoloDepth", p);
    };

};
