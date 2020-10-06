/*
  ==============================================================================

    SynthSound.h
    Created: 5 Oct 2020 7:19:24pm
    Author:  alext

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    virtual bool appliesToNote(int) // midiNoteNumber
    {
        return true;
    }

    virtual bool appliesToChannel(int) // midiChannel
    {
        return true;
    }
};
