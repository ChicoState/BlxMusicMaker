/*
  ==============================================================================

    BLXLookAndFeel.cpp
    Created: 25 Oct 2020 3:55:39pm
    Author: kyle 

  ==============================================================================
*/

#include "BLXLookAndFeel.h"

/*
windowBackground = 0,
widgetBackground,
menuBackground,
outline,
defaultText,
defaultFill,
highlightedText,
highlightedFill,
menuText,
*/

int BLXLookAndFeel::currentRadioID = 100;

BLXLookAndFeel::BLXLookAndFeel()
{
    LookAndFeel_V4 lookAndFeel;
    juce::LookAndFeel_V4::ColourScheme scheme(lookAndFeel.getDarkColourScheme());
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::windowBackground, juce::Colour::fromRGB(43, 44, 47));
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::widgetBackground, juce::Colour::fromRGB(26, 27, 28));
    //Light grey
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::defaultFill, juce::Colour::fromRGB(166, 166, 166));
    //Menu Color
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::menuBackground, juce::Colour::fromRGB(53, 55, 61));

    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::outline, juce::Colour::fromRGB(33, 34, 35));
    //scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::defaultText, juce::Colour::fromRGB(53, 55, 61));
    //scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::highlightedText, juce::Colour::fromRGB(53, 55, 61));

    //blue
    scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::highlightedFill, juce::Colour::fromRGB(33, 169, 255));
    //scheme.setUIColour(juce::LookAndFeel_V4::ColourScheme::menuText, juce::Colour::fromRGB(53, 55, 61));
    setColourScheme(scheme);
}

int BLXLookAndFeel::getNewRadioID()
{
    return currentRadioID++;
}

int BLXLookAndFeel::getPanelLabelHeight()
{
    return 25;
}

juce::Rectangle<int> BLXLookAndFeel::getEffectsInsetArea(juce::Rectangle<int> area)
{
    int panelInset = 4;
    area.removeFromTop(panelInset);
    area.removeFromLeft(panelInset / 2);
    area.removeFromRight(panelInset);
    area.removeFromBottom(panelInset);
    return area;
}

juce::Rectangle<int> BLXLookAndFeel::getWaveInsetArea(juce::Rectangle<int> area)
{
    int panelInset = 4;
    area.removeFromTop(panelInset);
    area.removeFromLeft(panelInset);
    area.removeFromRight(panelInset / 2);
    area.removeFromBottom(panelInset / 2);
    return area;
}

juce::Rectangle<int> BLXLookAndFeel::getEnvelopeInsetArea(juce::Rectangle<int> area)
{
    int panelInset = 4;
    area.removeFromTop(panelInset / 2);
    area.removeFromLeft(panelInset);
    area.removeFromRight(panelInset / 2);
    area.removeFromBottom(panelInset);
    return area;
}

void BLXLookAndFeel::drawMenuBarBackground(Graphics& g, int width, int height, bool isMouseOverBar, MenuBarComponent& menuBar)
{
    Rectangle<int> r(width, height);
    BLXLookAndFeel blx;
    g.setColour(blx.getCurrentColourScheme().getUIColour(BLXLookAndFeel::ColourScheme::menuBackground));
    g.fillRect(r);
}
