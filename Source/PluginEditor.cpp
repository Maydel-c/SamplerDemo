/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerDemoAudioProcessorEditor::SamplerDemoAudioProcessorEditor (SamplerDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), mWaveThumbnail(p), audioProcessor (p)
{
    // Attack
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mAttackSlider.setRange(0.0, 5.0, 0.01);
    mAttackSlider.addListener(this);
    addAndMakeVisible(mAttackSlider);
    
    mAttackLabel.setFont(juce::Font(juce::Font(juce::FontOptions(10))));
    mAttackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    mAttackLabel.setJustificationType(juce::Justification::centredTop);
    mAttackLabel.attachToComponent(&mAttackSlider, false);
    
    // Decay
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setRange(0.0, 5.0, 0.01);
    mDecaySlider.addListener(this);
    addAndMakeVisible(mDecaySlider);
    
    mDecayLabel.setFont(juce::Font(juce::Font(juce::FontOptions(10))));
    mDecayLabel.setText("Decay", juce::NotificationType::dontSendNotification);
    mDecayLabel.setJustificationType(juce::Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false);
    
    // Sustain
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setRange(0.0, 1.0, 0.01);
    mSustainSlider.addListener(this);
    addAndMakeVisible(mSustainSlider);
    
    mSustainLabel.setFont(juce::Font(juce::Font(juce::FontOptions(10))));
    mSustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
    mSustainLabel.setJustificationType(juce::Justification::centredTop);
    mSustainLabel.attachToComponent(&mSustainSlider, false);
    
    // Release
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::red);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mReleaseSlider.setRange(0.0, 5.0, 0.01);
    mReleaseSlider.addListener(this);
    addAndMakeVisible(mReleaseSlider);
    
    mReleaseLabel.setFont(juce::Font(juce::Font(juce::FontOptions(10))));
    mReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    mReleaseLabel.setJustificationType(juce::Justification::centredTop);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);
    
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
    const auto startX = 0.6f;
    const auto startY = 0.5f;
    const auto dialWidth = 0.1f;
    const auto dialHeight = 0.4f;
    mAttackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
    mDecaySlider.setBoundsRelative(startX + dialWidth, startY, dialWidth, dialHeight);
    mSustainSlider.setBoundsRelative(startX + 2*dialWidth, startY, dialWidth, dialHeight);
    mReleaseSlider.setBoundsRelative(startX + 3*dialWidth, startY, dialWidth, dialHeight);
    
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
            shouldBePainting = true;
            audioProcessor.loadFile(file);
        }
    }
   
    repaint();
}

void SamplerDemoAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) { 
    if (slider == &mAttackSlider)
    {
        audioProcessor.getADSRParams().attack = mAttackSlider.getValue();
    }
    else if (slider == &mDecaySlider)
    {
        audioProcessor.getADSRParams().decay = mDecaySlider.getValue();
    }
    else if (slider == &mSustainSlider)
    {
        audioProcessor.getADSRParams().sustain = mSustainSlider.getValue();
    }
    else if (slider == &mReleaseSlider)
    {
        audioProcessor.getADSRParams().release = mReleaseSlider.getValue();
    }
    
    audioProcessor.updateADSR();
}

