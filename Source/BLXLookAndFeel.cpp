/*
  ==============================================================================

    BLXLookAndFeel.cpp
    Created: 25 Oct 2020 3:55:39pm
    Author: kyle 

  ==============================================================================
*/

#include "BLXLookAndFeel.h"

BLXLookAndFeel::BLXLookAndFeel()
{
    LookAndFeel_V4 lookAndFeel;
    juce::LookAndFeel_V4::ColourScheme scheme(lookAndFeel.getDarkColourScheme());
    //Medium Grey
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::windowBackground, juce::Colour::fromRGB(43, 44, 47));
    //Dark grey
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::widgetBackground, juce::Colour::fromRGB(26, 27, 28));
    //Light grey
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::defaultFill, juce::Colour::fromRGB(166, 166, 166));
    //Menu Color
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::menuBackground, juce::Colour::fromRGB(53, 55, 61));
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::outline, juce::Colour::fromRGB(33, 34, 35));
    //blue
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::highlightedFill, juce::Colour::fromRGB(33, 169, 255));

    setColourScheme(scheme);
}

void BLXLookAndFeel::drawMenuBarBackground(Graphics& g, int width, int height, bool isMouseOverBar, MenuBarComponent& menuBar)
{
    Rectangle<int> r(width, height);
    g.setColour(getCurrentColourScheme().getUIColour(ColourScheme::menuBackground));
    g.fillRect(r);
}

void BLXLookAndFeel::drawTickBox(Graphics& g, Component& component, float x, float y, float w, float h, 
    const bool ticked, const bool isEnabled, const bool shouldDrawButtonAsHighlighted, const bool shouldDrawButtonAsDown)
{
    ignoreUnused (isEnabled, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

    Rectangle<float> tickBounds (x, y, w, h);

    g.setColour (getCurrentColourScheme().getUIColour(ColourScheme::widgetBackground));
    g.fillRect(tickBounds);

    if (ticked)
    {
        g.setColour (getCurrentColourScheme().getUIColour(ColourScheme::highlightedFill));
        auto tick = getTickShape (0.75f);
        g.fillPath (tick, tick.getTransformToScaleToFit (tickBounds.reduced (4, 5).toFloat(), false));
    }
}

