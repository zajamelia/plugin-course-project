#pragma once

namespace tremolo {
class Tremolo {
public:
  Tremolo() {
    lfo.setFrequency(5.f /*Hz*/, true);
  }
  void prepare(double sampleRate, int expectedMaxFramesPerBlock) {
    const juce::dsp::ProcessSpec processSpec{
    .sampleRate = sampleRate,
    .maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
    .numChannels = 1u, // Same LFO applied to all channels therefore put 1 for numChannels
    };
    lfo.prepare(processSpec);
  }

  void process(juce::AudioBuffer<float>& buffer) noexcept {
    // for each frame
    for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {
      // generate the LFO value
      const auto lfoValue = lfo.processSample(0.f); // Get next LFO value (0 is  dummy input which is ignored by the oscillator)

      // calculate the modulation value
      constexpr auto modulationDepth = 0.4f;
      const auto modulationValue = modulationDepth * lfoValue + 1.f; // LFO value converted into a volume multiplier (multiplied with audio sample to create tremolo effect)


      // for each channel sample in the frame
      for (const auto channelIndex :
           std::views::iota(0, buffer.getNumChannels())) {
        // get the input sample
        const auto inputSample = buffer.getSample(channelIndex, frameIndex);

        // modulate the sample
        const auto outputSample = inputSample * modulationValue;

        // set the output sample
        buffer.setSample(channelIndex, frameIndex, outputSample);
      }
    }
  }

  void reset() noexcept {
    lfo.reset();
  }

private:
  // You should put class members and private functions here
  juce::dsp::Oscillator<float>lfo{[](auto phase){return std::sin(phase);}}; // Created oscillator with mapping function

};
}  // namespace tremolo
