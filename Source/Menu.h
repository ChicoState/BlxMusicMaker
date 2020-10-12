#pragma once
#include <JuceHeader.h>

class Menu : public juce::Component, public juce::MenuBarModel
{
public:
    Menu();
    ~Menu() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
    void menuBarActivated(bool isActive) override;

private:
    juce::MenuBarComponent menu;
};

