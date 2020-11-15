/*
  ==============================================================================

    StateManager.cpp
    Created: 10 Nov 2020 1:03:54pm
    Author: kyle 

  ==============================================================================
*/

#include "StateManager.h"

StateManager StateManager::instance;

void StateManager::setTreeState(juce::AudioProcessorValueTreeState& tree) 
{
    treeState = &tree;
    currentPreset = treeState->state.getPropertyAsValue("Preset", nullptr).getValue();
}

StateManager& StateManager::get()
{
    return instance;
}

void StateManager::saveCurrentPreset()
{
    juce::File file(getFilePath(currentPreset));
    juce::FileOutputStream outStream(file);
    if (outStream.failedToOpen()) {
        juce::Logger::writeToLog("failed to open output stream");
        return;
    }
    file.deleteFile();
    juce::Logger::writeToLog("Saving");
    treeState->state.writeToStream(outStream);

    juce::Logger::writeToLog(file.getFullPathName());
    juce::Logger::writeToLog(treeState->state.toXmlString());
}

void StateManager::loadPreset(juce::String presetName)
{
    juce::File file(getFilePath(presetName));
    juce::FileInputStream inStream(file);
    if (inStream.openedOk()) 
    {
        treeState->replaceState(treeState->state.readFromStream(inStream));
        juce::Logger::writeToLog("Opened file");
        juce::Logger::writeToLog(treeState->state.toXmlString());
        currentPreset = presetName;
    }
    else
    {
        juce::Logger::writeToLog("Failed to open file");
    }
}

void StateManager::createPreset(juce::String presetName)
{
    currentPreset = presetName;
    treeState->state.setProperty("Preset", presetName, nullptr);
    juce::File file(getFilePath(currentPreset));
    file.create();
}

juce::String StateManager::getFilePath(juce::String presetName)
{
    return "F:/BlxMusicMaker/Builds/VisualStudio2019/x64/Debug/" + presetName;
}


