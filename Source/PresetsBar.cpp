#include "PresetsBar.h"

PresetsBar::PresetsBar()
{
	menu.setModel(this);
	addAndMakeVisible(menu);

	saveButton.setButtonText("Save");
	saveButton.onClick = [this] { onSaveClick(); };
	addAndMakeVisible(saveButton);
}

PresetsBar::~PresetsBar()
{
}

void PresetsBar::paint(juce::Graphics& g)
{
}

void PresetsBar::resized()
{
	juce::Rectangle<int> area = getLocalBounds();
	menu.setBounds(area.removeFromLeft(200));
	saveButton.setBounds(area.removeFromLeft(50));
}

void PresetsBar::onSaveClick()
{
}

juce::StringArray PresetsBar::getMenuBarNames()
{
	juce::StringArray menus;
	menus.add("Presets");
	menus.add("Create Preset");
	return menus;
}

juce::PopupMenu PresetsBar::getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName)
{
	juce::PopupMenu popUp;
	switch (topLevelMenuIndex)
	{
	case 1:
		popUp.addItem(1, "preset1");
		popUp.addItem(2, "preset2");
		popUp.addItem(3, "preset3");
		break;
	default:
		popUp.addItem(1, "load preset1");
		popUp.addItem(2, "load preset2");
		popUp.addItem(3, "load preset3");
		break;
	}
	return popUp;
}

void PresetsBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	/*
	switch (topLevelMenuIndex)
	{
	case 1:
		StateManager::get().createPreset("Preset" + std::to_string(menuItemID));
		break;
	default:
		StateManager::get().loadPreset("Preset" + std::to_string(menuItemID));
		break;
	}
	*/
}

void PresetsBar::menuBarActivated(bool isActive)
{
}
