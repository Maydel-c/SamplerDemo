/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerDemoAudioProcessorEditor::SamplerDemoAudioProcessorEditor (SamplerDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

SamplerDemoAudioProcessorEditor::~SamplerDemoAudioProcessorEditor()
{
}

//==============================================================================
void SamplerDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    
    auto bounds = getLocalBounds();
    g.setFont(15.0f);
    g.setColour(juce::Colours::white);
    
    // if we have a sound
    if(audioProcessor.getNumSamplerSounds() > 0)
    {
        // display "sound loaded"
        g.fillAll(juce::Colours::red);
        g.drawText("Sound Loaded", bounds, juce::Justification::centred);
    }
    // else display "load a sound"
    else
    {
        g.drawText("Please load a sound", bounds, juce::Justification::centred);
    }
}

void SamplerDemoAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

bool SamplerDemoAudioProcessorEditor::isInterestedInFileDrag (const juce::StringArray& files)
{
    
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains("aif"))
        {
            return true;
        }
    }
    
    return false;
}

void SamplerDemoAudioProcessorEditor::filesDropped (const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(file))
        {
            audioProcessor.loadFile(file);
        }
    }
   
    repaint();
}
