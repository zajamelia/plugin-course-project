namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p),
    rateAttachment{p.getParameterRefs().rate,rateSlider}, depthAttachment{p.getParameterRefs().depth,depthSlider}{
  background.setImage(juce::ImageCache::getFromMemory(
      assets::Background_png, assets::Background_pngSize));

  logo.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

  addAndMakeVisible(background);
  addAndMakeVisible(logo);
  addAndMakeVisible(lfoVisualizer);

  rateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary); // Slider type
  rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false,0,0); // Removes text box
  rateSlider.setPopupDisplayEnabled(true,true,this); // Shows chosen preset when user hovers
  rateSlider.setTextValueSuffix("Hz");
  addAndMakeVisible(rateSlider);

  depthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false,0,0);
  depthSlider.setPopupDisplayEnabled(true,true,this);
  addAndMakeVisible(depthSlider);




  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 300);
}

    void PluginEditor::resized()
{
    auto bounds = getLocalBounds();

    auto backgroundBounds = bounds;
    backgroundBounds.removeFromBottom(30);
    background.setBounds(backgroundBounds);

    logo.setBounds({16, 16, 105, 24});
    lfoVisualizer.setBounds({18, 149, 504, 92});

    rateSlider.setBounds(180, 40, 100, 100);

    auto depthSliderBounds = bounds;
    depthSliderBounds.removeFromLeft(280);
    depthSliderBounds.removeFromRight(180);
    depthSliderBounds.removeFromTop(40);
    depthSliderBounds.removeFromBottom(150);
    depthSlider.setBounds(depthSliderBounds);
}
}  // namespace tremolo
