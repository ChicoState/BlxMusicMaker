/*
  ==============================================================================

    MyUnitTest.h
    Created: 2 Dec 2020 1:39:52pm
    Author:  alext

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class MyUnitTest : public juce::UnitTest
{
public:
    MyUnitTest();
    void runTest() override;
};
