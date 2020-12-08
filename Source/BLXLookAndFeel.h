/*
  ==============================================================================

    BLXLookAndFeel.h
    Created: 25 Oct 2020 3:55:39pm
    Author: kyle 

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
using namespace juce;

class BLXLookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    BLXLookAndFeel();
    void drawMenuBarBackground (Graphics&, int width, int height, bool isMouseOverBar, MenuBarComponent&) override;
    void drawTickBox(Graphics& g, Component& component, float x, float y, float w, float h, const bool ticked,
        const bool isEnabled, const bool shouldDrawButtonAsHighlighted, const bool shouldDrawButtonAsDown) override;

};
