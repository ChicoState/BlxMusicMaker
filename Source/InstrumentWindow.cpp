#include "InstrumentWindow.h"

InstrumentWindow::InstrumentWindow()
{
	addAndMakeVisible(instrumentPanel);
	addAndMakeVisible(instrumentEditorPanel);
}

InstrumentWindow::~InstrumentWindow()
{
}

void InstrumentWindow::paint(juce::Graphics&)
{
}

void InstrumentWindow::resized()
{
	auto area = getLocalBounds();
	instrumentPanel.setBounds(area.removeFromLeft(300));
	instrumentEditorPanel.setBounds(area.removeFromTop(getHeight() / 2));
}
