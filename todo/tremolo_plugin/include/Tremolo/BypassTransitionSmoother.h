#pragma once

namespace tremolo {
/**
 * Class facilitating transition to and from bypassed state over a single block.
 *
 * It allows 2 things:
 *  - detecting that a bypass state transition takes place
 *  - fade-in and fade-out of dry (unprocessed) and wet (processed) buffers
 *    according to the transition type
 *
 * Use the following code in the processBlock() method of your plugin processor:
 *
 * @code
 * //...
 *
 * bypassTransitionSmoother.setBypass(parameters.bypassed);
 *
 * if (bypassTransitionSmoother.isTransitioning()) {
 *   bypassTransitionSmoother.setDryBuffer(buffer);
 *
 *   yourAudioEffectClassInstance.process(buffer);
 *
 *   bypassTransitionSmoother.mixToWetBuffer(buffer);
 *
 *   return;
 * }
 *
 * // avoid processing if bypassed, process otherwise...
 * @endcode
 *
 * Alternatively, you can unconditionally call setDryBuffer() and
 * mixToWetBuffer(), like this:
 *
 * @code
 * //...
 *
 * bypassTransitionSmoother.setBypass(parameters.bypassed);
 *
 * if (parameters.bypassed && !bypassTransitionSmoother.isTransitioning()) {
 *   // avoid processing if the plugin is bypassed
 *   return;
 * }
 *
 * bypassTransitionSmoother.setDryBuffer(buffer);
 * yourAudioEffectClassInstance.process(buffer);
 * bypassTransitionSmoother.mixToWetBuffer(buffer);
 *
 * // no more processing necessary
 * @endcode
 *
 * Remember to call prepare() in prepareToPlay(),
 * setBypassForced() in setStateInformation(), and reset() in
 * releaseResources().
 */
class BypassTransitionSmoother {
public:
  explicit BypassTransitionSmoother(double crossfadeLengthSecondsValue = 0.01)
      : crossfadeLengthSeconds{crossfadeLengthSecondsValue} {
    jassert(0.0 < crossfadeLengthSeconds);
  }

  void prepare(const juce::dsp::ProcessSpec& spec) {
    sampleRateHz = spec.sampleRate;
    dryBuffer.setSize(static_cast<int>(spec.numChannels),
                      static_cast<int>(spec.maximumBlockSize)); // Allocate memory to store dry signal
    dryGain.reset(spec.sampleRate, crossfadeLengthSeconds);
    wetGain.reset(spec.sampleRate, crossfadeLengthSeconds);
  }

  void setBypass(bool bypass) noexcept {
    const auto current = dryGain.getCurrentValue();
    const auto target = bypass ? 1.0f : 0.0f; // condition ? value_if_true : value_if_false
    const auto duration = crossfadeLengthSeconds * std::abs(target - current); // Calculate duration of transition

    dryGain.reset(sampleRateHz, duration); //Update smoothing time
    wetGain.reset(sampleRateHz, duration);

    dryGain.setCurrentAndTargetValue(current); // Start dry gain from current value
    dryGain.setTargetValue(target); // Move dry gain to target value

    wetGain.setCurrentAndTargetValue(1.0f - current); // Do the same for wet but in opposite direction
    wetGain.setTargetValue(1.0f - target);
  }

  //Instantly change bypass (no smoothing)
  void setBypassForced(bool bypass) noexcept {
    dryGain.setCurrentAndTargetValue(bypass ? 1.0f : 0.0f); // Set dry gain
    wetGain.setCurrentAndTargetValue(1.0f - dryGain.getTargetValue()); // Set wet again to opposite value
  }

  [[nodiscard]] bool isTransitioning() const noexcept {
    return dryGain.isSmoothing() || wetGain.isSmoothing(); // Transition continues til both are finnished
  }

  //Saves copy of dry audio
  void setDryBuffer(const juce::AudioBuffer<float>& buffer) noexcept {
    jassert(buffer.getNumSamples() <= dryBuffer.getNumSamples());
    jassert(buffer.getNumChannels() <= dryBuffer.getNumChannels());

    for (const auto channel : std::views::iota(0, buffer.getNumChannels())) {
      dryBuffer.copyFrom(channel, 0, buffer, channel, 0,
                         buffer.getNumSamples());
    }
    dryGain.applyGain(dryBuffer, buffer.getNumSamples()); // Applies current dry gain
  }

  void mixToWetBuffer(juce::AudioBuffer<float>& buffer) noexcept {
    jassert(buffer.getNumSamples() <= dryBuffer.getNumSamples());
    jassert(buffer.getNumChannels() <= dryBuffer.getNumChannels());

    wetGain.applyGain(buffer, buffer.getNumSamples());

    //Add dry buffer to wet buffer
    for (const auto channel : std::views::iota(0, buffer.getNumChannels())) {
      buffer.addFrom(channel, 0, dryBuffer, channel, 0, buffer.getNumSamples());
    }
  }

  void reset() noexcept {
    setBypassForced(false);
    dryBuffer.clear();
  }

private:
  double crossfadeLengthSeconds = 0.0;
  double sampleRateHz = 0.0;
  juce::LinearSmoothedValue<float> dryGain{0.f};
  juce::LinearSmoothedValue<float> wetGain{1.f};
  juce::AudioBuffer<float> dryBuffer; // store original audio
};
}  // namespace tremolo
