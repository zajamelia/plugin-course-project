
namespace tremolo {
  namespace {

    juce::AudioParameterFloat& createModulationRateParameter(juce::AudioProcessor& processor)
    {
      constexpr auto versionHint = 1;

      auto parameter = std::make_unique<juce::AudioParameterFloat>(
          juce::ParameterID{"modulation.rate", versionHint},
          "Modulation rate",
          juce::NormalisableRange<float>{0.1f, 20.f, 0.01f, 0.4f},
          5.f, juce::AudioParameterFloatAttributes{}.withLabel("Hz"));

      auto& parameterReference = *parameter;
      processor.addParameter(parameter.release());
      return parameterReference;
    }



  }

  Parameters::Parameters(juce::AudioProcessor& processor)
      : rate{createModulationRateParameter(processor)}
  {
  }

} // namespace tremolo
