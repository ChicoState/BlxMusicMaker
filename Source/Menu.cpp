#include "Menu.h"

Menu::Menu()
{
	menu.setModel(this);
	addAndMakeVisible(menu);
}

Menu::~Menu()
{
}

void Menu::paint(juce::Graphics&)
{
}

void Menu::resized()
{
	juce::Rectangle<int> area = getLocalBounds();
	menu.setBounds(area);
}

juce::StringArray Menu::getMenuBarNames()
{
	juce::StringArray menus;
	menus.add("File");
	menus.add("Options");
	return menus;
}

juce::PopupMenu Menu::getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName)
{
	juce::PopupMenu popUp;
	popUp.addItem(1, "test");
	popUp.addItem(2, "test1");
	popUp.addItem(3, "test2");
	return popUp;
}

void Menu::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
}

void Menu::menuBarActivated(bool isActive)
{
}
