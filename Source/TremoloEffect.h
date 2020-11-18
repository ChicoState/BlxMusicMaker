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

    TremoloEffect() : EffectParent::EffectParent("Tremolo")
    {
        EffectParent::addSpeedComponent("Speed", "TremoloSpeed");
        EffectParent::addSliderComponent("Depth", "TremoloDepth");
    };

};
