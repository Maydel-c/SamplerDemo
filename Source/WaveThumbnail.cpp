/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 22 Nov 2024 3:20:37pm
    Author:  Abhinav

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"

//==============================================================================
WaveThumbnail::WaveThumbnail(SamplerDemoAudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveThumbnail::~WaveThumbnail()
{
}

void WaveThumbnail::paint (juce::Graphics& g)
{
    
    g.fillAll(juce::Colours::cadetblue.darker());
    
    auto waveform = audioProcessor.getWaveForm();
    
//    if(shouldBePainting)
    if(waveform.getNumSamples() > 0)
    {
        
        juce::Path p;
        mAudioPoints.clear();
        
        auto ratio = waveform.getNumSamples() / getWidth();
        
        auto buffer = waveform.getReadPointer(0);
        
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
        
        p.startNewSubPath(0, getHeight() / 2);
        
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0);
            p.lineTo(sample, point);
        }
        
        g.strokePath(p, juce::PathStrokeType(2));
        
//        shouldBePainting = false;
    }
}

void WaveThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

bool WaveThumbnail::isInterestedInFileDrag (const juce::StringArray& files)
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

void WaveThumbnail::filesDropped (const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(file))
        {
//            shouldBePainting = true;
            audioProcessor.loadFile(file);
        }
    }
   
    repaint();
}
