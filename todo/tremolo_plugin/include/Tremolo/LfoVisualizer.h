namespace tremolo {
    class LfoVisualizer : public juce::Component {

    private:
        juce::Path waveformPath;
        float strokeWidth = 4.f;
        Tremolo::LfoWaveform currentWaveform = Tremolo::LfoWaveform::sine;


    public:
        void setLfoWaveform(Tremolo::LfoWaveform waveform) {
            currentWaveform = waveform;
            resized();
        }

        // Only job: draw path
        void paint(juce::Graphics& g) override {
            g.setColour(juce::Colours::aqua);
            g.strokePath(waveformPath, juce::PathStrokeType{strokeWidth});
            }
        // Rebuild path whenever component size changes
        void resized() override {
            const auto halfHeight = getHeight()/2;
            const auto amplitude = halfHeight - strokeWidth / 2.f;
            if (currentWaveform == Tremolo::LfoWaveform::sine)
            {
                waveformPath.clear();
                waveformPath.startNewSubPath(-2.f,halfHeight + amplitude * std::sin(0.1f * -2.f));
                for (const auto x: std::views::iota(-2,getWidth()+2)){
                    waveformPath.lineTo(x,halfHeight + amplitude * std::sin(0.1f* x));
                }
            }
            else
            {
                waveformPath.clear();
                waveformPath.startNewSubPath(-2.f,halfHeight + amplitude * Tremolo::triangle(0.1f * -2.f));
                for (const auto x: std::views::iota(-2,getWidth()+2)){
                    waveformPath.lineTo(x,halfHeight + amplitude * Tremolo::triangle(0.1f* x));
                }

            }



        }

    };
}