/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveThumbnail.h"

//==============================================================================
/**
*/
class SamplerDemoAudioProcessorEditor  :    public juce::AudioProcessorEditor //,
//                                            public juce::Slider::Listener
{
public:
    SamplerDemoAudioProcessorEditor (SamplerDemoAudioProcessor&);
    ~SamplerDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
//    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    juce::Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;
    
    WaveThumbnail mWaveThumbnail;
    SamplerDemoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerDemoAudioProcessorEditor)
};
