#include "InstrumentEditorPanel.h"

InstrumentEditorPanel::InstrumentEditorPanel()
{
	panelLabel.setText("Editor", juce::NotificationType::dontSendNotification);
	addAndMakeVisible(panelLabel);
	addAndMakeVisible(selector);
	addAndMakeVisible(sliders);
}

InstrumentEditorPanel::~InstrumentEditorPanel()
{
}

void InstrumentEditorPanel::paint(juce::Graphics& g)
{
	g.setColour(juce::Colours::white);
	g.drawRect(getLocalBounds());
}

void InstrumentEditorPanel::resized()
{
	auto area = getLocalBounds();
	area.reduce(10, 0);
	panelLabel.setBounds(area.removeFromTop(30));
	selector.setBounds(area.removeFromLeft(330));
	sliders.setBounds(area);
}
