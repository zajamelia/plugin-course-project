#pragma once

namespace tremolo {
struct Parameters {
  explicit Parameters(juce::AudioProcessor&);

  juce::AudioParameterFloat& rate;

  JUCE_DECLARE_NON_COPYABLE(Parameters); // "Nobody is allowed to make a copy of this class"
  JUCE_DECLARE_NON_MOVEABLE(Parameters);
};
}  // namespace tremolo
