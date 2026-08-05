namespace tremolo {
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p),
    rateAttachment{p.getParameterRefs().rate,rateSlider}{
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

  lfoCurveWidthSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
  lfoCurveWidthSlider.setRange(0,10,1);
    lfoCurveWidthSlider.onValueChange = [this]
    {
        lfoVisualizer.setStrokeWidth(lfoCurveWidthSlider.getValue());
    };

  addAndMakeVisible(lfoCurveWidthSlider);


  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(540, 300);
}

void PluginEditor::resized() {
 auto bounds = getLocalBounds();

 auto backgroundBounds = bounds;
 backgroundBounds.removeFromBottom(30);
 background.setBounds(backgroundBounds);

 logo.setBounds({16, 16, 105, 24});
 lfoVisualizer.setBounds({18,149,504,92});


  auto rateSliderBounds = bounds;
  rateSliderBounds.removeFromLeft(230);
  rateSliderBounds.removeFromRight(230);
  rateSliderBounds.removeFromTop(40);
  rateSliderBounds.removeFromBottom(150);
  rateSlider.setBounds(rateSliderBounds);

  auto controlPanelBounds = bounds;
  controlPanelBounds.removeFromTop(bounds.getHeight() - 30);

  auto lfoCurveWidthSliderBounds = controlPanelBounds;
    lfoCurveWidthSliderBounds.removeFromLeft(10);
    lfoCurveWidthSliderBounds.removeFromRight(controlPanelBounds.getWidth()/2);
    lfoCurveWidthSliderBounds.removeFromTop(10);
    lfoCurveWidthSliderBounds.removeFromBottom(10);
    lfoCurveWidthSlider.setBounds(lfoCurveWidthSliderBounds);



}
}  // namespace tremolo
