/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "maximilian.h"

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
            std::make_unique<juce::AudioParameterInt>("Wave", "Wave", 0, 6, 0),

            //ADSR
            std::make_unique<juce::AudioParameterFloat>("Attack", "Attack", 0, 5000, 0.1f),
            std::make_unique<juce::AudioParameterFloat>("Decay", "Decay", 0, 5000, 500.0f),
            std::make_unique<juce::AudioParameterFloat>("Sustain", "Sustain", 0.0f, 1.0f, 0.125f),
            std::make_unique<juce::AudioParameterFloat>("Release", "Release", 0, 5000, 100.0f),

            //Effects Panel
            std::make_unique<juce::AudioParameterBool>("Arpeggiator", "ArpeggiatorToggle", false),
            std::make_unique<juce::AudioParameterInt>("ArpegSpeed", "ArpegSpeed", 0, 5, 0),

            std::make_unique<juce::AudioParameterBool>("Tremolo", "TremoloToggle", false),
            std::make_unique<juce::AudioParameterInt>("TremoloSpeed", "TremoloSpeed", 0, 5, 0),
            std::make_unique<juce::AudioParameterFloat>("TremoloDepth", "TremoloDepth", 0.01, 0.50, 0.01),

            std::make_unique <juce::AudioParameterBool>("Vibrato", "VibratoToggle", false),
            std::make_unique<juce::AudioParameterInt>("VibratoSpeed", "VibratoSpeed", 0, 5, 0),
            std::make_unique<juce::AudioParameterInt>("VibratoDepth", "VibratoDepth", 1, 16, 1),

            std::make_unique<juce::AudioParameterBool>("Note Slide", "NoteSlideToggle", false),
            std::make_unique<juce::AudioParameterInt>("NoteSlideSpeed", "NoteSlideSpeed", 0, 5, 0),
            std::make_unique<juce::AudioParameterInt>("NoteSlideDepth", "NoteSlideDepth", -12, 12, 0)
        }),
    myVoice(&SynthVoice()),
    lastSampleRate(48000),
    audioPlayHead(this->getPlayHead()),
    currentPositionInfo(juce::AudioPlayHead::CurrentPositionInfo())
#endif
{
    StateManager::get().setTreeState(treeState);

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
    // ensures initialized sample rate
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

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // set adsr from tree
	std::atomic<float>* a =
		StateManager::get().treeState->getRawParameterValue("Attack");
    attackTime = *a;
	std::atomic<float>* d =
		StateManager::get().treeState->getRawParameterValue("Decay");
    decayTime = *d;
	std::atomic<float>* s =
		StateManager::get().treeState->getRawParameterValue("Sustain");
    sustainTime = *s;
	std::atomic<float>* r =
		StateManager::get().treeState->getRawParameterValue("Release");
    releaseTime = *r;

    for (int i = 0; i < mySynth.getNumVoices(); ++i)
    {
		// adjust the parameters of the voice
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            myVoice->getParam(attackTime, decayTime, sustainTime, releaseTime, currentPositionInfo.bpm,
                currentPositionInfo.timeSigNumerator, currentPositionInfo.timeSigDenominator);
            myVoice->setMaxiSettings(lastSampleRate, totalNumOutputChannels, buffer.getNumSamples());
        }
    }

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool BlxMusicMakerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BlxMusicMakerAudioProcessor::createEditor()
{
    return new BlxMusicMakerAudioProcessorEditor (*this);
}

//==============================================================================
void BlxMusicMakerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = StateManager::get().treeState->copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void BlxMusicMakerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(StateManager::get().treeState->state.getType())) 
        {
            StateManager::get().treeState->replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BlxMusicMakerAudioProcessor();
}
