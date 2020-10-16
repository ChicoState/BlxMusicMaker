#pragma once
#include <JuceHeader.h>

class InstrumentList : public juce::Component
{
public:
    InstrumentList();
    ~InstrumentList() override;

    int getInstrumentStackHeight();

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    int buttonHeight = 100;
    juce::TextButton button1;
    juce::TextButton button2;
    juce::TextButton button3;
    juce::TextButton button4;
};

class InstrumentPanel : public juce::Component
{
public:
    InstrumentPanel();
    ~InstrumentPanel() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Label panelLabel;
    juce::Viewport viewPort;
    InstrumentList instrumentList;
};
