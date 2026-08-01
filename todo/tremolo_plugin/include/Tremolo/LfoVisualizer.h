namespace tremolo {
    class LfoVisualizer : public juce::Component {
    public:
        void paint(juce::Graphics& g) override {
            juce::Path sine;

            const auto strokeWidth = 4.f;
            const auto halfHeight = getHeight()/2; // Vertical centre of component
            const auto amplitude = halfHeight - strokeWidth / 2.f; // Subtract half the stroke width to avoid clipping

            sine.startNewSubPath(0.f,halfHeight + amplitude * std::sin(0.f));

            for (const auto x: std::views::iota(1,getWidth())){
                sine.lineTo(x,halfHeight + amplitude * std::sin(0.1* x));
            }
            g.setColour(juce::Colours::aqua);
            g.strokePath(sine, juce::PathStrokeType{strokeWidth});

        }

    };
}