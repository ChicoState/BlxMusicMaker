Blx Music Maker

Blx Music Maker is a simple VST with 8-bit sounds.

## Current Features ##
 - Seven different sounds: Sine, Saw, 3 types of Pulse, Noise, and Triangle
 - ASDR sliders
 - Midi Input
 - Opens in FL Studio
 - Stylized by Kyle Rhoads

## Getting Started ##
If you're on Windows and use Visual Studio 2019:
 - You will need JUCE installed (https://juce.com/get-juce)
 - You'll need to link the Maximilian Sound library to the JUCE project
 - You will also need to build an Audio Plugin Host (located in the main JUCE directory),
   and hook that up to the project. This is because VST3's are not standalone, and rely
   on hosts such as FL studio.

## How to open on FL Studio ##
 - Currently, this is only possible on Windows.
 - Install the VST3 by clicking on BlxMusicMaker-windows.exe. It will install in the correct
   directory on its own.
 - Open FL Studio, and to Options-> Manage Plugins-> Find More Plugins. It will scan your 
   computer to find new VSTs.
 - BlxMusicMaker will now show up as a new VST. Click on the star icon next to it, so that
   it shows up on the channel rack.
 - Press F6 to open the channel rack.
