#pragma once
#include <JuceHeader.h>
#include "StateManager.h"
#include "BLXLookAndFeel.h"

class PresetsBar : public juce::Component, public juce::MenuBarModel
{
public:
    PresetsBar();
    ~PresetsBar() override;

    void onSaveClick();

    void paint(juce::Graphics&) override;
    void resized() override;

    juce::StringArray getMenuBarNames() override;
    juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;
    void menuBarActivated(bool isActive) override;

private:
    juce::MenuBarComponent menu;
    juce::TextButton saveButton;
};

