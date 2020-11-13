/*
  ==============================================================================

    StateManager.cpp
    Created: 10 Nov 2020 1:03:54pm
    Author: kyle 

  ==============================================================================
*/

#include "StateManager.h"

StateManager StateManager::instance;

StateManager::~StateManager()
{
    delete treeState;
    delete undoManager;
}

void StateManager::SetAudioProcessor(juce::AudioProcessor& processor) {
    undoManager = new juce::UndoManager;
    treeState = new juce::AudioProcessorValueTreeState(processor, undoManager, "Params",
    {
		std::make_unique<juce::AudioParameterBool>("Arpeggiator", "ArpeggiatorToggle", false),
		std::make_unique<juce::AudioParameterBool>("Tremolo", "TremoloToggle", false),
		std::make_unique <juce::AudioParameterBool>("Vibrato", "VibratoToggle", false),
		std::make_unique<juce::AudioParameterBool>("Note Slide", "NoteSlideToggle", false),
		std::make_unique<juce::AudioParameterInt>("ArpegSpeed", "ArpegSpeed", 0, 3, 0)
    });
    Load();
}

StateManager& StateManager::get()
{
    return instance;
}

void StateManager::Save()
{
    juce::File file("F:/BlxMusicMaker/Builds/VisualStudio2019/x64/Debug/Save");
    if (file.exists()) 
    {
        file.deleteFile();
        juce::Logger::writeToLog("file deleted");
    }
    juce::FileOutputStream outStream(file);
    if (outStream.failedToOpen()) {
        juce::Logger::writeToLog("failed to open output stream");
        return;
    }
    juce::Logger::writeToLog("Saving");
    treeState->state.writeToStream(outStream);

    juce::Logger::writeToLog(file.getFullPathName());
    juce::Logger::writeToLog(treeState->state.toXmlString());
}

void StateManager::Load()
{
    juce::File file("F:/BlxMusicMaker/Builds/VisualStudio2019/x64/Debug/Save");
    juce::FileInputStream inStream(file);
    if (inStream.openedOk()) 
    {
        treeState->replaceState(treeState->state.readFromStream(inStream));
        juce::Logger::writeToLog("Opened file");
        juce::Logger::writeToLog(treeState->state.toXmlString());
    }
    else
    {
        juce::Logger::writeToLog("Failed to open file");
    }
}


