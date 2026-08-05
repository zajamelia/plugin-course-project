#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  void resized() override;

  juce::ImageComponent background;
  juce::ImageComponent logo;

  LfoVisualizer lfoVisualizer;

  juce::Slider rateSlider;
  juce::SliderParameterAttachment rateAttachment;
  juce::Slider lfoCurveWidthSlider;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
