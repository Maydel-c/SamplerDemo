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
    setSize (600, 200);
}

SamplerDemoAudioProcessorEditor::~SamplerDemoAudioProcessorEditor()
{
}

//==============================================================================
void SamplerDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    
    g.setColour(juce::Colours::white);
    
    if(shouldBePainting)
    {
        juce::Path p;
        mAudioPoints.clear();
        
        auto waveform = audioProcessor.getWaveForm();
        auto ratio = waveform.getNumSamples() / getWidth();
        
        auto buffer = waveform.getReadPointer(0);
        
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
        
        p.startNewSubPath(0, getHeight() / 2);
        
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1, 1, 200, 0);
            p.lineTo(sample, point);
        }
        
        g.strokePath(p, juce::PathStrokeType(2));
        
        shouldBePainting = false;
    }
    // new file dropped?
        // if yes
            // get the waveform from the processor
            // find scaling ratio: sample = 44100(1 sec)... x axis of the window = 600 == sampleLength /getWidth()
            // values of the audioFile -1 to 1 map to y axis values 200 to 0 (acc to window size)
            // use the ratio to take values from the aduio buffer and put it in vector to display
            // draw the waveform
    
    
//    auto bounds = getLocalBounds();
//    g.setFont(15.0f);
//    g.setColour(juce::Colours::white);
//
//    // if we have a sound
//    if(audioProcessor.getNumSamplerSounds() > 0)
//    {
//        // display "sound loaded"
//        g.fillAll(juce::Colours::red);
//        g.drawText("Sound Loaded", bounds, juce::Justification::centred);
//    }
//    // else display "load a sound"
//    else
//    {
//        g.drawText("Please load a sound", bounds, juce::Justification::centred);
//    }
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
            shouldBePainting = true;
        }
    }
   
    repaint();
}
