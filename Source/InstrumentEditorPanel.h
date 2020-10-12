#pragma once
#include <JuceHeader.h>

class TypeSelector;
class EnvelopeSliders;

class InstrumentEditorPanel : public juce::Component
{
public:
    InstrumentEditorPanel();
    ~InstrumentEditorPanel() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Label* panelLabel;
    TypeSelector* selector;
    EnvelopeSliders* sliders;
};


class TypeSelector : public juce::Component
{
public:
    TypeSelector();
    ~TypeSelector() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void updateToggleState(juce::TextButton*);
    juce::TextButton* buttons;
    int radioId = 1001;
};


class EnvelopeSliders : public juce::Component
{
public:
    EnvelopeSliders();
    ~EnvelopeSliders() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(int);

private:
    juce::Slider* sliders;
    juce::Label* labels;
};
