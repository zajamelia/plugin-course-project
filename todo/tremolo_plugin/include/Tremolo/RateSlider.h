#pragma once

namespace tremolo {
    class RateSlider : public juce::Slider {
    public:
        void paint(juce::Graphics& g) override {
            auto sliderPos = (float) valueToProportionOfLength (getValue());
            jassert (sliderPos >= 0 && sliderPos <= 1.0f);
            auto outline = findColour (Slider::rotarySliderOutlineColourId);
            auto fill    = findColour (Slider::rotarySliderFillColourId);

            const auto rotaryParams = getRotaryParameters();
            const auto rotaryStartAngle = rotaryParams.startAngleRadians;
            const auto rotaryEndAngle = rotaryParams.endAngleRadians;

            auto bounds = getLocalBounds().toFloat().reduced (10);

            auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);



            if (isEnabled())
            {
                juce::Path valueArc;
                valueArc.addPieSegment(bounds.toFloat(),rotaryStartAngle, toAngle,0.f);

                g.setColour (juce::Colours::aqua);
                g.fillPath (valueArc);
            }

        }

    };
}
