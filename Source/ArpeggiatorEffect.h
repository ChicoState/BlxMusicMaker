/*
  ==============================================================================

    ArpeggiatorEffect.h
    Created: 28 Oct 2020 6:10:36pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "EffectParent.h"

class ArpeggiatorEffect : public EffectParent
{
public:

    ArpeggiatorEffect(BlxMusicMakerAudioProcessor& p) : EffectParent("Arpeggiator", p) 
    {
        addSpeedComponent("Speed", "ArpegSpeed", p);
    };

};
