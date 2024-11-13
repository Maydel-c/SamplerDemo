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
    mLoadButton.onClick = [&](){ audioProcessor.loadFile(); };
    
    addAndMakeVisible(mLoadButton);
    setSize (200, 200);
}

SamplerDemoAudioProcessorEditor::~SamplerDemoAudioProcessorEditor()
{
}

//==============================================================================
void SamplerDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SamplerDemoAudioProcessorEditor::resized()
{
    mLoadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
}
