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
class WaveThumbnail  : public juce::Component
{
public:
    WaveThumbnail(SamplerDemoAudioProcessor& p); // Don't forget to pass in the processor
    ~WaveThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    SamplerDemoAudioProcessor& audioProcessor;
    
    bool shouldBePainting { false };
    std::vector<float> mAudioPoints;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
