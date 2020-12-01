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
            std::make_unique<juce::AudioParameterFloat>("Attack", "Attack", 0, 5000, 0.2f),
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
    lastSampleRate(48000.0f),
    audioPlayHead(this->getPlayHead()),
    currentPositionInfo(juce::AudioPlayHead::CurrentPositionInfo()),
    currentNote(0), lastNoteValue(-1), time(0)
#endif
{
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
    return internalPresetNames->length();   
    // NB: some hosts don't cope very well if you tell them there are 0 programs,
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
    if(index == 0)
        return "InternalTest";
    if (index == 1)
        return "InternalTest2";
    if (index == 2)
        return "InternalTest3";
    if (index == 3)
        return "InternalTest4";
    return "Default";
}

void BlxMusicMakerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BlxMusicMakerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // ensures initialized sample rate
    juce::ignoreUnused(samplesPerBlock);
    notes.clear();
    currentNote = 0;
    lastNoteValue = -1;
    time = 0;
    lastSampleRate = static_cast<float>(sampleRate);
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
    auto numSamples = buffer.getNumSamples();

    audioPlayHead = this->getPlayHead();
    audioPlayHead->getCurrentPosition(currentPositionInfo);
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, numSamples);

    // arp
    int speed = (int) *treeState.getRawParameterValue("ArpegSpeed");
    bool arpActive = *treeState.getRawParameterValue("Arpeggiator") > 0.5f;

    if (arpActive)
    {
        // do arp stuff
        auto noteDuration = static_cast<int> (std::ceil(lastSampleRate * getArpDuration(speed)));
        for (const auto metadata : midiMessages)
        {
            const auto msg = metadata.getMessage();
            if (msg.isNoteOn())  notes.add(msg.getNoteNumber());
            else if (msg.isNoteOff()) notes.removeValue(msg.getNoteNumber());
        }
        midiMessages.clear();
        if (time + numSamples >= noteDuration)
        {
            auto offset = jmax(0, jmin((int)(noteDuration - time), numSamples - 1));
            if (lastNoteValue > 0)
            {
                midiMessages.addEvent(juce::MidiMessage::noteOff(1, lastNoteValue), offset);
                lastNoteValue = -1;
            }

            if (notes.size() > 0)
            {
                currentNote = (currentNote + 1) % notes.size();
                lastNoteValue = notes[currentNote];
                midiMessages.addEvent(juce::MidiMessage::noteOn(1, lastNoteValue, (uint8)127), offset);
            }
        }

        time = (time + numSamples) % noteDuration;
    }
    else if (notes.size() > 0) notes.clear();

    for (int i = 0; i < mySynth.getNumVoices(); ++i)
    {
		// adjust the parameters of the voice
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            myVoice->getParam(
                treeState.getRawParameterValue("Wave"),
                treeState.getRawParameterValue("Attack"),
                treeState.getRawParameterValue("Decay"),
                treeState.getRawParameterValue("Sustain"),
                treeState.getRawParameterValue("Release"),
                treeState.getRawParameterValue("Tremolo"),
                treeState.getRawParameterValue("TremoloSpeed"),
                treeState.getRawParameterValue("TremoloDepth"),
                treeState.getRawParameterValue("Vibrato"),
                treeState.getRawParameterValue("VibratoSpeed"),
                treeState.getRawParameterValue("VibratoDepth"),
                treeState.getRawParameterValue("Note Slide"),
                treeState.getRawParameterValue("NoteSlideSpeed"),
                treeState.getRawParameterValue("NoteSlideDepth"),
                currentPositionInfo.bpm);
            myVoice->setMaxiSettings(lastSampleRate, totalNumOutputChannels, numSamples);
        }
    }

    mySynth.renderNextBlock(buffer, midiMessages, 0, numSamples);
}

float BlxMusicMakerAudioProcessor::getArpDuration(int speed)
{
    // thirty second note returns => 1/64
    float bpm2Sec = 60 / currentPositionInfo.bpm;
    switch (speed)
    {
    case 0: // 1/32
        return (float)0.125 * bpm2Sec;
    case 1: // 1/16
        return (float)0.25 * bpm2Sec;
    case 2: // 1/8
        return (float)0.5 * bpm2Sec;
    case 3: // 1/4
        return (float)1 * bpm2Sec;
    case 4: // 1/2
        return (float)2 * bpm2Sec;
    case 5: // 1/1
        return (float)4 * bpm2Sec;
    }
    return (float)0.125 * bpm2Sec;
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
void BlxMusicMakerAudioProcessor::getStateInformation(juce::MemoryBlock & destData)
{
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void BlxMusicMakerAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(treeState.state.getType())) 
            treeState.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BlxMusicMakerAudioProcessor();
}
