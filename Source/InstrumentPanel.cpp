#include "InstrumentPanel.h"

InstrumentList::InstrumentList()
{
	addAndMakeVisible(button1);
	addAndMakeVisible(button2);
	addAndMakeVisible(button3);
	addAndMakeVisible(button4);
	setSize(292, getInstrumentStackHeight());
}

InstrumentList::~InstrumentList()
{
}

void InstrumentList::paint(juce::Graphics&)
{
}

void InstrumentList::resized()
{
	auto area = getLocalBounds();
	button1.setBounds(area.removeFromTop(buttonHeight));
	button2.setBounds(area.removeFromTop(buttonHeight));
	button3.setBounds(area.removeFromTop(buttonHeight));
	button4.setBounds(area.removeFromTop(buttonHeight));
}

int InstrumentList::getInstrumentStackHeight() {
	return buttonHeight * 4;
}

//InstrumentPanel (Parent)

InstrumentPanel::InstrumentPanel()
{
	viewPort.setViewedComponent(&instrumentList);
	panelLabel.setText("Instruments", juce::NotificationType::dontSendNotification);
	addAndMakeVisible(panelLabel);
	addAndMakeVisible(viewPort);
}

InstrumentPanel::~InstrumentPanel()
{
}

void InstrumentPanel::paint(juce::Graphics& g)
{
	g.setColour(juce::Colours::white);
	g.drawRect(getLocalBounds());
}

void InstrumentPanel::resized()
{
	auto area = getLocalBounds();
	panelLabel.setBounds(area.removeFromTop(30));
	viewPort.setBounds(area);
	viewPort.setSize(area.getWidth(), area.getHeight());
}
