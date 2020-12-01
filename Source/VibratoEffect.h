/*
  ==============================================================================

    VibratoEffect.h
    Created: 29 Oct 2020 7:42:03pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EffectParent.h" 

class VibratoEffect : public EffectParent  
{
public:

    VibratoEffect(BlxMusicMakerAudioProcessor& p) : EffectParent::EffectParent("Vibrato", p)
    {
        EffectParent::addSpeedComponent("Speed", "VibratoSpeed", p);
        EffectParent::addSliderComponent("Depth", "VibratoDepth", p);
    };

};

