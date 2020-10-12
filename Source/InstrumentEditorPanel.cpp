#include "InstrumentEditorPanel.h"

TypeSelector::TypeSelector()
{
	std::string buttonNames[] = { "Pulse", "Triangle", "Saw", "Sine", "Noise" };
	buttons = new juce::TextButton[5];
	for (int i = 0; i < 5; i++) {
		buttons[i].setButtonText(buttonNames[i]);
		buttons[i].setRadioGroupId(radioId);
		buttons[i].setClickingTogglesState(true);
		buttons[i].onClick = [this, i] { updateToggleState(&buttons[i]); };
		addAndMakeVisible(buttons[i]);
	}
}

TypeSelector::~TypeSelector()
{
	delete[] buttons;
}

void TypeSelector::paint(juce::Graphics& g)
{
}

void TypeSelector::resized()
{
	auto area = getLocalBounds();

	juce::FlexBox topFlexBox;
	topFlexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	topFlexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
	topFlexBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < 3; i++) {
		topFlexBox.items.add(juce::FlexItem(buttons[i]).withMinWidth(100).withMinHeight(100).withMargin(5));
	}
	topFlexBox.performLayout(area.removeFromTop(100));

	area.removeFromTop(10);
	juce::FlexBox bottomFlexBox;
	bottomFlexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	bottomFlexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
	bottomFlexBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 3; i < 5; i++) {
		bottomFlexBox.items.add(juce::FlexItem(buttons[i]).withMinWidth(100).withMinHeight(100).withMargin(5));
	}
	bottomFlexBox.performLayout(area.removeFromTop(100));
}

void TypeSelector::updateToggleState(juce::TextButton* button)
{
	if (button->getToggleState())
	{
		juce::Logger::writeToLog(button->getButtonText());
	}
}

//EnvelopeSliders

EnvelopeSliders::EnvelopeSliders()
{
	sliders = new juce::Slider[4];
	for (int i = 0; i < 4; i++) {
		sliders[i].setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
		sliders[i].setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
		sliders[i].onValueChange = [this, i] { sliderValueChanged(i); };
		addAndMakeVisible(sliders[i]);
	}

	std::string sliderNames[] = { "Attack", "Decay", "Sustain", "Release" };
	labels = new juce::Label[4];
	for (int i = 0; i < 4; i++) {
		labels[i].setText(sliderNames[i], juce::NotificationType::dontSendNotification);
		labels[i].setJustificationType(juce::Justification::centredTop);
		addAndMakeVisible(labels[i]);
	}
}

EnvelopeSliders::~EnvelopeSliders()
{
	delete[] sliders;
	delete[] labels;
}

void EnvelopeSliders::paint(juce::Graphics& g)
{
}

void EnvelopeSliders::resized()
{
	auto area = getLocalBounds();

	juce::FlexBox sliderBox;
	sliderBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	sliderBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
	sliderBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < 4; i++) {
		sliderBox.items.add(juce::FlexItem(sliders[i]).withMinWidth(50).withMinHeight(200));
	}
	sliderBox.performLayout(area.removeFromTop(200));

	juce::FlexBox labelBox;
	labelBox.flexWrap = juce::FlexBox::Wrap::noWrap;
	labelBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
	labelBox.alignContent = juce::FlexBox::AlignContent::center;
	for (int i = 0; i < 4; i++) {
		labelBox.items.add(juce::FlexItem(labels[i]).withMinWidth(50).withMinHeight(20));
	}
	labelBox.performLayout(area.removeFromTop(20));
}

void EnvelopeSliders::sliderValueChanged(int sliderIndex)
{
	juce::Logger::writeToLog(labels[sliderIndex].getText());
	juce::Logger::writeToLog(std::to_string(sliders[sliderIndex].getValue()));
}

//InstrumentEditorPanel (Parent)

InstrumentEditorPanel::InstrumentEditorPanel()
{
	panelLabel = new juce::Label;
	panelLabel->setText("Editor", juce::NotificationType::dontSendNotification);
	addAndMakeVisible(panelLabel);

	selector = new TypeSelector;
	addAndMakeVisible(selector);

	sliders = new EnvelopeSliders;
	addAndMakeVisible(sliders);
}

InstrumentEditorPanel::~InstrumentEditorPanel()
{
	delete panelLabel;
	delete selector;
	delete sliders;
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
	panelLabel->setBounds(area.removeFromTop(30));
	selector->setBounds(area.removeFromLeft(330));
	sliders->setBounds(area);
}
