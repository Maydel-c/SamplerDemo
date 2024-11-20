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
class SamplerDemoAudioProcessorEditor  :    public juce::AudioProcessorEditor,
                                            public juce::FileDragAndDropTarget,
                                            public juce::Slider::Listener
{
public:
    SamplerDemoAudioProcessorEditor (SamplerDemoAudioProcessor&);
    ~SamplerDemoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag (const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    std::vector<float> mAudioPoints;
    SamplerDemoAudioProcessor& audioProcessor;
    bool shouldBePainting { false };
    
    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
    juce::Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerDemoAudioProcessorEditor)
};
