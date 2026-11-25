#include "helpers/test_helpers.h"
#include <PluginProcessor.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE ("one is equal to one", "[dummy]")
{
    REQUIRE (1 == 1);
}

TEST_CASE ("Plugin instance", "[instance]")
{
    const juce::ScopedJuceInitialiser_GUI gui;
    PluginProcessor testPlugin;

    SECTION ("name")
    {
        CHECK_THAT (testPlugin.getName().toStdString(),
            Catch::Matchers::Equals ("AUDIO EQUALIZER"));
    }
}


#ifdef PAMPLEJUCE_IPP
    #include <ipps.h>

TEST_CASE ("IPP version", "[ipp]")
{
    CHECK_THAT (ippsGetLibVersion()->Version, Catch::Matchers::Equals ("2021.7 (r0xa954907f)"));
}
#endif

TEST_CASE ("Independent channel levels survive a state reload", "[gain]")
{
    const juce::ScopedJuceInitialiser_GUI gui;
    PluginProcessor processor;
    auto* left = processor.parameters.getParameter ("leftGain");
    auto* right = processor.parameters.getParameter ("rightGain");
    REQUIRE (left != nullptr);
    REQUIRE (right != nullptr);
    CHECK (left->getValue() == 1.0f);
    CHECK (right->getValue() == 1.0f);

    left->setValueNotifyingHost (0.5f);
    right->setValueNotifyingHost (0.0f);
    juce::MemoryBlock state;
    processor.getStateInformation (state);

    PluginProcessor restored;
    restored.setStateInformation (state.getData(), static_cast<int> (state.getSize()));
    restored.prepareToPlay (48000.0, 64);
    juce::AudioBuffer<float> audio (2, 64);
    for (int channel = 0; channel < audio.getNumChannels(); ++channel)
        juce::FloatVectorOperations::fill (audio.getWritePointer (channel), 1.0f, audio.getNumSamples());
    juce::MidiBuffer midi;
    restored.processBlock (audio, midi);
    CHECK (audio.getSample (0, 0) == 0.5f);
    CHECK (audio.getSample (1, 0) == 0.0f);
}
