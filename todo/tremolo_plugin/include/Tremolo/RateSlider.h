/* #pragma once

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
                valueArc.addCentredArc(
    bounds.getCentreX(),      // centre X position
    bounds.getCentreY(),      // centre Y position
    bounds.getWidth() / 2.f,  // horizontal radius
    bounds.getHeight() / 2.f, // vertical radius
    0.f,                      // rotation of the whole ellipse
    rotaryStartAngle,         // where arc starts
    toAngle,                  // where arc ends
    true                      // start a new path
);

                g.setColour (juce::Colours::aqua);
                g.strokePath(valueArc, juce::PathStrokeType(4.0f)
);
            }

        }

    };
} */
