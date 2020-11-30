/*
  ==============================================================================

    StateManager.h
    Created: 10 Nov 2020 1:03:54pm
    Author: kyle 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class StateManager
{
public:
    
    StateManager();
    static StateManager& get();
    void setTreeState(juce::AudioProcessorValueTreeState&);

    juce::AudioProcessorValueTreeState* treeState;

private:
    static StateManager instance;
};
