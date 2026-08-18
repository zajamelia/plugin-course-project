#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  void resized() override;



  juce::ImageComponent background;
  juce::ImageComponent logo;

  LfoVisualizer lfoVisualizer;
  CustomLookAndFeel lookAndFeel;

  juce::Slider rateSlider;
  juce::SliderParameterAttachment rateAttachment;

  juce::Slider depthSlider;
  juce::SliderParameterAttachment depthAttachment;

  juce::ToggleButton bypassButton{"BYPASSED"};
  juce::ButtonParameterAttachment bypassAttachment;



  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
