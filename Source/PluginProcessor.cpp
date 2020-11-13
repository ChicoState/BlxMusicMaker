/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "maximilian.h"

// default times for adsr
float BlxMusicMakerAudioProcessor::attackTime = 0.1; 
float BlxMusicMakerAudioProcessor::decayTime = 0.1;
float BlxMusicMakerAudioProcessor::sustainTime = 0.1;
float BlxMusicMakerAudioProcessor::releaseTime = 0.1;

//==============================================================================
BlxMusicMakerAudioProcessor::BlxMusicMakerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
	    #if ! JucePlugin_IsMidiEffect
		    #if ! JucePlugin_IsSynth
				.withInput("Input", juce::AudioChannelSet::stereo(), true)
		    #endif
				.withOutput("Output", juce::AudioChannelSet::stereo(), true)
	    #endif
    ),
	treeState(*this, &undoManager, "Params",
	{
		std::make_unique<juce::AudioParameterBool>("Arpeggiator", "ArpeggiatorToggle", false),
		std::make_unique<juce::AudioParameterInt>("ArpegSpeed", "ArpegSpeed", 0, 3, 0),

		std::make_unique<juce::AudioParameterBool>("Tremolo", "TremoloToggle", false),
		std::make_unique<juce::AudioParameterInt>("TremoloSpeed", "TremoloSpeed", 0, 3, 0),
		std::make_unique<juce::AudioParameterFloat>("TremoloDepth", "TremoloDepth", -12, 12, 0),

		std::make_unique <juce::AudioParameterBool>("Vibrato", "VibratoToggle", false),
		std::make_unique<juce::AudioParameterInt>("VibratoSpeed", "VibratoSpeed", 0, 3, 0),
		std::make_unique<juce::AudioParameterFloat>("VibratoDepth", "VibratoDepth", -12, 12, 0),

		std::make_unique<juce::AudioParameterBool>("Note Slide", "NoteSlideToggle", false),
		std::make_unique<juce::AudioParameterInt>("NoteSlideSpeed", "NoteSlideSpeed", 0, 3, 0),
		std::make_unique<juce::AudioParameterFloat>("NoteSlideDepth", "NoteSlideDepth", -1, 1, 0)
	})
#endif
{
    StateManager::get().SetTreeState(treeState);
    // init voices and add them to synth
    mySynth.clearVoices();
    int numVoices = 10;
    for (int i = 0; i < numVoices; i++)
        mySynth.addVoice(new SynthVoice());
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

BlxMusicMakerAudioProcessor::~BlxMusicMakerAudioProcessor()
{
}

//==============================================================================
const juce::String BlxMusicMakerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BlxMusicMakerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BlxMusicMakerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BlxMusicMakerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BlxMusicMakerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BlxMusicMakerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BlxMusicMakerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BlxMusicMakerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BlxMusicMakerAudioProcessor::getProgramName (int index)
{
    return {};
}

void BlxMusicMakerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BlxMusicMakerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // insures initialized sample rate
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
}

void BlxMusicMakerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BlxMusicMakerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BlxMusicMakerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    audioPlayHead = this->getPlayHead();
    audioPlayHead->getCurrentPosition(currentPositionInfo);
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
		// adjust the parameters of the voice
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            myVoice->getParam(attackTime, decayTime, sustainTime, releaseTime, currentPositionInfo.bpm,
                currentPositionInfo.timeSigNumerator, currentPositionInfo.timeSigDenominator);
            myVoice->setMaxiSettings(lastSampleRate, totalNumOutputChannels, buffer.getNumSamples());
        }
    }

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool BlxMusicMakerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BlxMusicMakerAudioProcessor::createEditor()
{
    //StateManager::get().Save();
    //StateManager::get().Load();
    return new BlxMusicMakerAudioProcessorEditor (*this);
}

//==============================================================================
void BlxMusicMakerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    StateManager::get().Save();
}

void BlxMusicMakerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //Load
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BlxMusicMakerAudioProcessor();
}
