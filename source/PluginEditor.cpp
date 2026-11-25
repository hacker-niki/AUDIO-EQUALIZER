#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p),
      leftAttachment (p.parameters, "leftGain", left),
      rightAttachment (p.parameters, "rightGain", right)
{
    addAndMakeVisible(right);
    addAndMakeVisible(left);
    addAndMakeVisible(left_label);
    addAndMakeVisible(right_label);

    left.setName ("Left channel");
    right.setName ("Right channel");
    left.setTextValueSuffix (" %");
    right.setTextValueSuffix (" %");

    right_label.setText("RIGHT channel", juce::dontSendNotification);
    left_label.setText("LEFT channel", juce::dontSendNotification);


    // this chunk of code instantiates and opens the melatonin inspector


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

}

void PluginEditor::resized()
{

    left.setSize(150, 50);
    left.setTopLeftPosition(50, 300);
    left.moved();


    right.setSize(150, 50);
    right.setTopLeftPosition(50, 350);
    right.moved();

    left_label.setSize(100, 30);
    left_label.setTopLeftPosition(50, 290);
    left_label.moved();

    right_label.setSize(100, 30);
    right_label.setTopLeftPosition(50, 340);
    right_label.moved();


    // layout the positions of your child components here
}
