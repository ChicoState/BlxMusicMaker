#pragma once
#include <JuceHeader.h>
#include "EnvelopeSliders.h"
#include "TypeSelector.h"

class InstrumentEditorPanel : public juce::Component
{
public:
    InstrumentEditorPanel();
    ~InstrumentEditorPanel() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Label panelLabel;
    TypeSelector selector;
    EnvelopeSliders sliders;
};

