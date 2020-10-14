#include "InstrumentWindow.h"

InstrumentWindow::InstrumentWindow()
{
	instrumentPanel = new InstrumentPanel;
	instrumentEditorPanel = new InstrumentEditorPanel();
	addAndMakeVisible(instrumentPanel);
	addAndMakeVisible(instrumentEditorPanel);
}

InstrumentWindow::~InstrumentWindow()
{
	delete instrumentPanel;
	delete instrumentEditorPanel;
}

void InstrumentWindow::paint(juce::Graphics&)
{
}

void InstrumentWindow::resized()
{
	auto area = getLocalBounds();
	instrumentPanel->setBounds(area.removeFromLeft(300));
	instrumentEditorPanel->setBounds(area.removeFromTop(getHeight() / 2));
}
