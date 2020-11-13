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
    
    StateManager() {};
    ~StateManager();
    static StateManager& get();
    void Save();
    void Load();

    void SetAudioProcessor(juce::AudioProcessor&);
    void SetProperty(std::string, int);

    juce::AudioProcessorValueTreeState* treeState;
    juce::UndoManager* undoManager;

private:

    static StateManager instance;

};
