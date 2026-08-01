namespace tremolo {
    class LfoVisualizer : public juce::Component {

    private:
        juce::Path sine;
        float strokeWidth = 4.f;


    public:
        // Only job: draw path
        void paint(juce::Graphics& g) override {
            g.setColour(juce::Colours::aqua);
            g.strokePath(sine, juce::PathStrokeType{strokeWidth});
            }
        // Rebuild path whenever component size changes
        void resized() override {
            sine.clear();
            const auto halfHeight = getHeight()/2;
            const auto amplitude = halfHeight - strokeWidth / 2.f;
            sine.startNewSubPath(-2.f,halfHeight + amplitude * std::sin(0.f));
            for (const auto x: std::views::iota(-2,getWidth()+2)){
                sine.lineTo(x,halfHeight + amplitude * std::sin(0.1* x));
            }


        }

    };
}