Blx Music Maker

Blx Music Maker is a simple VST with 8-bit sounds.

![Plugin Image](https://i.imgur.com/YoJpD7g.png)

## Current Features ##
 - Seven different sounds: sine, saw, three types of pulse, noise, and triangle
 - ASDR sliders
 - Midi support
 - Vibrato 
 - Tremolo 
 - Note slides
 - Arpeggiation 
 - Saving/loading presets
 - Verified to work with FL Studio
 - Stylized by Kyle Rhoads!

## Getting Started ##
If you're on Windows and use Visual Studio 2019:
 - You will need JUCE installed (https://juce.com/get-juce).
 - You'll need to link the Maximilian Sound library to the JUCE project.
 - You will also need to build an Audio Plugin Host (located in the main JUCE directory),
   and hook that up to the project. This is because VST3's are not standalone, and rely
   on hosts such as FL studio.

## How to Install ##
 - The VST3 file needs to be put in a location your DAW checks for plugins.
   - For mac, it's either Macintosh HD/Library/Audio/Plug-Ins/VST3 or ~/Library/Audio/Plug-Ins/VST3.
   - For windows, its C:\Program Files\Common Files\VST3.
 - If you're on Windows, you can use the BlxMusicMaker.exe (located in the Output directory),
   and it will install in the correct location.

## How to Open on FL Studio ##
 - Install the VST3.
 - Open FL Studio, and to Options-> Manage Plugins-> Find More Plugins. It will scan your 
   computer to find new VSTs.
 - BlxMusicMaker will now show up as a new VST. Click on the star icon next to it, so that
   it shows up on the channel rack.
 - Press F6 to open the channel rack.
