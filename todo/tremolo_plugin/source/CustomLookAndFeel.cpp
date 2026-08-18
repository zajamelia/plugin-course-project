namespace tremolo {
    void CustomLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton & button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
        const auto bounds = button.getLocalBounds().reduced(2);

        if (shouldDrawButtonAsHighlighted) {
            g.setOpacity(0.7f);

        }

        if (button.getToggleState()) {
            auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xFFFF901A },juce::Colour{0xFFFFC300}, bounds);
            if (shouldDrawButtonAsHighlighted) {
                buttonGradient.multiplyOpacity(0.7f);
            }
            g.setGradientFill(buttonGradient);
            g.fillRoundedRectangle(bounds.toFloat(),4.f);
            ;
            g.setColour(juce::Colour{0xFF501A0B});
        }
        else {
            auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xFF4A7090 },juce::Colour{0xFF324358}, bounds);
            buttonGradient.addColour(0.73,juce::Colour{0xFF315160});
            if (shouldDrawButtonAsHighlighted) {
                buttonGradient.multiplyOpacity(0.7f);
            }
            g.setGradientFill(buttonGradient);
            g.fillRoundedRectangle(bounds.toFloat(),4.f);
            ;
            g.setColour(juce::Colour{0xFFDDECFF});
        }
        g.drawText(button.getButtonText(),bounds,juce::Justification::centred, false);


    }
}  // namespace tremolo
