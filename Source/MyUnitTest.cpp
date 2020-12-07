/*
  ==============================================================================

    MyUnitTest.cpp
    Created: 2 Dec 2020 1:39:52pm
    Author:  alext

  ==============================================================================
*/

#include "MyUnitTest.h"

MyUnitTest::MyUnitTest() : UnitTest("SynthVoice Testing")
{
}

void MyUnitTest::runTest() 
{
    beginTest("Part 1");
    expect(1 == 1);
    expect(1 == 2);
}
