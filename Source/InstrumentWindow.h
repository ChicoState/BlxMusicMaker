#pragma once

#include <JuceHeader.h>
#include "InstrumentPanel.h"
#include "InstrumentEditorPanel.h"

class InstrumentWindow : public juce::Component
{
public:
    InstrumentWindow();
    ~InstrumentWindow() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    InstrumentPanel instrumentPanel;
    InstrumentEditorPanel instrumentEditorPanel;
};
