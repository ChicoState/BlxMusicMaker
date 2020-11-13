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
    
    static StateManager& get();
    void Save();
    void Load();

    void SetTreeState(juce::AudioProcessorValueTreeState&);

    juce::AudioProcessorValueTreeState* treeState;

private:

    StateManager() {};
    static StateManager instance;

};
