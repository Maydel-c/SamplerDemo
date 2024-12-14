/*
  ==============================================================================

    WaveThumbnail.h
    Created: 22 Nov 2024 3:20:37pm
    Author:  Abhinav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class WaveThumbnail  :  public juce::Component,
                        public juce::FileDragAndDropTarget
{
public:
    WaveThumbnail(SamplerDemoAudioProcessor& p); // Don't forget to pass in the processor
    ~WaveThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    bool isInterestedInFileDrag (const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;

private:
    
    SamplerDemoAudioProcessor& audioProcessor;
    
    bool shouldBePainting { false };
    std::vector<float> mAudioPoints;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
