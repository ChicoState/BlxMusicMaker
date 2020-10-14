/*
  ==============================================================================

    TypeSelector.h
    Created: 13 Oct 2020 9:28:10pm
    Author:  alext

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

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
