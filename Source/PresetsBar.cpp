#include "PresetsBar.h"

PresetsBar::PresetsBar()
{
	menu.setModel(this);
	addAndMakeVisible(menu);
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
	menu.setBounds(area);
}

juce::StringArray PresetsBar::getMenuBarNames()
{
	juce::StringArray menus;
	menus.add("File");
	menus.add("Options");
	return menus;
}

juce::PopupMenu PresetsBar::getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName)
{
	juce::PopupMenu popUp;
	popUp.addItem(1, "test");
	popUp.addItem(2, "test1");
	popUp.addItem(3, "test2");
	return popUp;
}

void PresetsBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
}

void PresetsBar::menuBarActivated(bool isActive)
{
}
