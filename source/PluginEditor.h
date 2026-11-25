#pragma once

#include "PluginProcessor.h"
#include "BinaryData.h"
// #include "melatonin_inspector/melatonin_inspector.h"

//==============================================================================
class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor (PluginProcessor&);
    ~PluginEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider left;
    juce::Slider right;
    juce::Label left_label;
    juce::Label right_label;
    juce::AudioProcessorValueTreeState::SliderAttachment leftAttachment, rightAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};
