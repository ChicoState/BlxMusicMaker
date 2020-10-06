/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

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
		attackTime(.1f),
		releaseTime(.1f),
		tree(*this, nullptr)
#endif
{
    // add parameters to attack and release tree
    juce::NormalisableRange<float> attackParam(attackTime, 5000);
    tree.createAndAddParameter("attack", "Attack", "Attack", attackParam,
        attackTime, nullptr, nullptr);

    juce::NormalisableRange<float> releaseParam(releaseTime, 5000);
    tree.createAndAddParameter("release", "Release", "Release", releaseParam,
        releaseTime, nullptr, nullptr);
    
    tree.state = juce::ValueTree("Sliders");

    // init voices and add them to synth
    mySynth.clearVoices();
    int numVoices = 10;
    for (int i = 0; i < numVoices; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    // insures initialized sample rate
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
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

    for (int i = 0; i < mySynth.getNumVoices(); i++)
    {
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            // adjust the parameters of the voice
            myVoice->getParam(tree.getRawParameterValue("attack"),
                tree.getRawParameterValue("release"));
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
    return new BlxMusicMakerAudioProcessorEditor (*this);
}

//==============================================================================
void BlxMusicMakerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BlxMusicMakerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BlxMusicMakerAudioProcessor();
}
