/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SamplerDemoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SamplerDemoAudioProcessorEditor (SamplerDemoAudioProcessor&);
    ~SamplerDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::TextButton mLoadButton { "Load" };
    SamplerDemoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerDemoAudioProcessorEditor)
};
