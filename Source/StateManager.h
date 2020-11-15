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
    void saveCurrentPreset();
    void loadPreset(juce::String);
    void createPreset(juce::String);

    void setTreeState(juce::AudioProcessorValueTreeState&);

    juce::AudioProcessorValueTreeState* treeState;

private:

    StateManager() {};
    juce::String getFilePath(juce::String);
    juce::String currentPreset;
    static StateManager instance;

};
