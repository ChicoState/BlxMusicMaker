/*
  ==============================================================================

    StateManager.cpp
    Created: 10 Nov 2020 1:03:54pm
    Author: kyle 

  ==============================================================================
*/

#include "StateManager.h"

StateManager StateManager::instance;

StateManager::StateManager()
{
    treeState = 0;
}

void StateManager::setTreeState(juce::AudioProcessorValueTreeState& tree) 
{
    treeState = &tree;
}

StateManager& StateManager::get()
{
    return instance;
}
