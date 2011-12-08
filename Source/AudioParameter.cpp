/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Nov 2011 9:34:25am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "SineAudioSource.cpp"
//[/Headers]

#include "AudioParameter.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#define T(stringLiteral)            JUCE_T(stringLiteral)
//[/MiscUserDefs]

//==============================================================================
AudioParameter::AudioParameter (int order_, SineAudioSource* ref_, GUIcomponent* const gui_)
    : order(order_),
      propertySlider (0),
      AlarmSelect (0),
      textOrder (0),
      vitalSelect (0),
      upperTh (0),
      lowerTh (0),
      fileLabel (0),
      val (0),
      upperLabel (0),
      lowerLabel (0),
      urgencyLabel (0),
      urgencyValue (0),
      threshLabel (0),
      threshVal (0),
      toggleContinuous (0)
{
    addAndMakeVisible (propertySlider = new Slider (L"slider"));
    propertySlider->setRange (0, 1, 0.05);
    propertySlider->setSliderStyle (Slider::Rotary);
    propertySlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    propertySlider->addListener (this);

    addAndMakeVisible (AlarmSelect = new ComboBox (L"Alarm Select"));
    AlarmSelect->setTooltip (L"Alarm type to sound");
    AlarmSelect->setEditableText (false);
    AlarmSelect->setJustificationType (Justification::centredLeft);
    AlarmSelect->setTextWhenNothingSelected (L"Alarm Type");
    AlarmSelect->setTextWhenNoChoicesAvailable (L"(no choices)");
    AlarmSelect->addItem (L"Noise", 1);
    AlarmSelect->addItem (L"Amp Mod", 2);
    AlarmSelect->addItem (L"Freq Mod", 3);
    AlarmSelect->addItem (L"Distortion", 4);
    AlarmSelect->addItem (L"Harmony", 5);
    AlarmSelect->addItem (L"Sheppard (Up)", 6);
    AlarmSelect->addItem (L"Sheppard (Dn)", 7);
    AlarmSelect->addItem (L"Pulse Width", 8);
    AlarmSelect->addItem (L"Sound File", 9);
    AlarmSelect->addItem (L"MATLAB", 10);
    AlarmSelect->addListener (this);

    addAndMakeVisible (textOrder = new TextEditor (L"Order Box"));
    textOrder->setTooltip (L"Alarm Order");
    textOrder->setMultiLine (false);
    textOrder->setReturnKeyStartsNewLine (false);
    textOrder->setReadOnly (false);
    textOrder->setScrollbarsShown (false);
    textOrder->setCaretVisible (true);
    textOrder->setPopupMenuEnabled (true);
    textOrder->setText (String::empty);

    addAndMakeVisible (vitalSelect = new ComboBox (L"Vital Select"));
    vitalSelect->setTooltip (L"Vital sign to monitor");
    vitalSelect->setEditableText (false);
    vitalSelect->setJustificationType (Justification::centredLeft);
    vitalSelect->setTextWhenNothingSelected (L"Vital Sign");
    vitalSelect->setTextWhenNoChoicesAvailable (L"(no choices)");
    vitalSelect->addItem (L"Heart Rate", 1);
    vitalSelect->addItem (L"SpO2", 2);
    vitalSelect->addItem (L"Resp Rate (AS/3)", 3);
    vitalSelect->addItem (L"Systolic BP", 4);
    vitalSelect->addItem (L"Diastolic BP", 5);
    vitalSelect->addItem (L"Mean BP", 6);
    vitalSelect->addItem (L"Temp", 7);
    vitalSelect->addItem (L"ST elevation", 8);
    vitalSelect->addItem (L"ETCO2", 9);
    vitalSelect->addItem (L"Tidal Volume", 10);
    vitalSelect->addItem (L"Minute Volume", 11);
    vitalSelect->addItem (L"O2 Level", 12);
    vitalSelect->addItem (L"Resp Rate (Aestiva)", 13);
    vitalSelect->addItem (L"Max Peak Pressure", 14);
    vitalSelect->addItem (L"FIO2", 15);
    vitalSelect->addItem (L"FIAA", 16);
    vitalSelect->addItem (L"pPeak-airway", 17);
    vitalSelect->addItem (L"PEEP", 18);
    vitalSelect->addItem (L"Min Vol Exp", 19);
    vitalSelect->addItem (L"PCWP", 20);
    vitalSelect->addListener (this);

    addAndMakeVisible (upperTh = new Slider (String::empty));
    upperTh->setRange (0, 1, 0);
    upperTh->setSliderStyle (Slider::TwoValueHorizontal);
    upperTh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    upperTh->addListener (this);

    addAndMakeVisible (lowerTh = new Slider (String::empty));
    lowerTh->setRange (0, 1, 0);
    lowerTh->setSliderStyle (Slider::TwoValueHorizontal);
    lowerTh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    lowerTh->addListener (this);

    addAndMakeVisible (fileLabel = new Label (L"File Lable",
                                              String::empty));
    fileLabel->setFont (Font (10.1000f, Font::plain));
    fileLabel->setJustificationType (Justification::centredLeft);
    fileLabel->setEditable (false, false, false);
    fileLabel->setColour (TextEditor::textColourId, Colours::black);
    fileLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (val = new Slider (L"Value Slider"));
    val->setRange (0, 1, 0);
    val->setSliderStyle (Slider::LinearHorizontal);
    val->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    val->setColour (Slider::backgroundColourId, Colour (0xffffff));
    val->setColour (Slider::thumbColourId, Colours::black);
    val->setColour (Slider::trackColourId, Colour (0xffffff));
    val->setColour (Slider::rotarySliderFillColourId, Colour (0xffffff));
    val->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffffff));
    val->addListener (this);

    addAndMakeVisible (upperLabel = new Label (L"Upper Threshold",
                                               L"Upper Thresholds"));
    upperLabel->setFont (Font (15.0000f, Font::plain));
    upperLabel->setJustificationType (Justification::centredLeft);
    upperLabel->setEditable (false, false, false);
    upperLabel->setColour (TextEditor::textColourId, Colours::black);
    upperLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (lowerLabel = new Label (L"Lower Threshold",
                                               L"Lower Thresholds"));
    lowerLabel->setFont (Font (15.0000f, Font::plain));
    lowerLabel->setJustificationType (Justification::centredLeft);
    lowerLabel->setEditable (false, false, false);
    lowerLabel->setColour (TextEditor::textColourId, Colours::black);
    lowerLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (urgencyLabel = new Label (String::empty,
                                                 L"Urgency:"));
    urgencyLabel->setFont (Font (11.0000f, Font::plain));
    urgencyLabel->setJustificationType (Justification::centredLeft);
    urgencyLabel->setEditable (false, false, false);
    urgencyLabel->setColour (TextEditor::textColourId, Colours::black);
    urgencyLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (urgencyValue = new Label (String::empty,
                                                 String::empty));
    urgencyValue->setFont (Font (11.0000f, Font::plain));
    urgencyValue->setJustificationType (Justification::centredLeft);
    urgencyValue->setEditable (false, false, false);
    urgencyValue->setColour (Label::backgroundColourId, Colours::white);
    urgencyValue->setColour (TextEditor::textColourId, Colours::black);
    urgencyValue->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (threshLabel = new Label (String::empty,
                                                String::empty));
    threshLabel->setFont (Font (11.0000f, Font::plain));
    threshLabel->setJustificationType (Justification::centredLeft);
    threshLabel->setEditable (false, false, false);
    threshLabel->setColour (Label::textColourId, Colours::black);
    threshLabel->setColour (TextEditor::textColourId, Colours::black);
    threshLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (threshVal = new Label (String::empty,
                                              String::empty));
    threshVal->setFont (Font (11.0000f, Font::plain));
    threshVal->setJustificationType (Justification::centredLeft);
    threshVal->setEditable (false, false, false);
    threshVal->setColour (Label::backgroundColourId, Colours::white);
    threshVal->setColour (TextEditor::textColourId, Colours::black);
    threshVal->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (toggleContinuous = new ToggleButton (L"Continuous Sonification"));
    toggleContinuous->setButtonText (L"Sonify");
    toggleContinuous->addListener (this);


    //[UserPreSize]
	// register callback on texbox change
	textOrder->addListener (this);

	// show values of threshold sliders
	val->setPopupDisplayEnabled(true, this);
	upperTh->setPopupDisplayEnabled(true, this);
	lowerTh->setPopupDisplayEnabled(true, this);

    //[/UserPreSize]

    setSize (780, 80);


    //[Constructor] You can add your own custom stuff here..
	ref = ref_;
	gui=gui_;

	updateStopLight();

	// glow effect
	glow = new GlowEffect();
	glow->setGlowProperties(GLOW_RAD, Colours::yellow);

	// register with sineAudioSource
	ref->addParam();

	// set the text box to the proper order
	textOrder->setText (String::String(order));

	startTimer(100);
    //[/Constructor]
}

AudioParameter::~AudioParameter()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	upperTh->setComponentEffect(NULL);
	lowerTh->setComponentEffect(NULL);
	delete glow;
    //[/Destructor_pre]

    deleteAndZero (propertySlider);
    deleteAndZero (AlarmSelect);
    deleteAndZero (textOrder);
    deleteAndZero (vitalSelect);
    deleteAndZero (upperTh);
    deleteAndZero (lowerTh);
    deleteAndZero (fileLabel);
    deleteAndZero (val);
    deleteAndZero (upperLabel);
    deleteAndZero (lowerLabel);
    deleteAndZero (urgencyLabel);
    deleteAndZero (urgencyValue);
    deleteAndZero (threshLabel);
    deleteAndZero (threshVal);
    deleteAndZero (toggleContinuous);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AudioParameter::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffecefff));

    //[UserPaint] Add your own custom painting code here..
	Path p;
	g.setOpacity(1.f);

	p.addRectangle(startx, yPos, dangerLowWidth, heightBar);// danger low
	p.addRectangle(startDangerHigh, yPos, dangerHighWidth, heightBar);// danger high
	g.setColour(Colours::red);	// paint red
	g.fillPath(p, AffineTransform());

	p.clear();
	p.addRectangle(startWarningLow, yPos, warningLowWidth, heightBar);// warning low
	p.addRectangle(startWarningHigh, yPos, warningHighWidth, heightBar);// warning high
	g.setColour(Colours::yellow);	//paint yellow
	g.fillPath(p, AffineTransform());

	p.clear();
	p.addRectangle(startNormal, yPos, normalWidth, heightBar);// normal
	g.setColour(Colours::green);	// paint green
	g.fillPath(p, AffineTransform());

	if (this->isMouseOver(true)){
		// this paints a rectangle around the component when a mouse is over it
		g.setColour (Colour (0x2f1dcac4));
		g.drawRect (0, 0, AudioParameter::getWidth(), AudioParameter::getHeight(), 3);
	}
	if(!this->hasKeyboardFocus(true))
		textOrder->setText (String::String(order));

    //[/UserPaint]
}

void AudioParameter::resized()
{
    propertySlider->setBounds (59, 5, 63, 64);
    AlarmSelect->setBounds (133, 26, 155, 24);
    textOrder->setBounds (8, 16, 32, 24);
    vitalSelect->setBounds (304, 26, 136, 24);
    upperTh->setBounds (448, 2, 312, 32);
    lowerTh->setBounds (448, 42, 312, 32);
    fileLabel->setBounds (0, 64, 480, 16);
    val->setBounds (448, 30, 312, 16);
    upperLabel->setBounds (351, 4, 104, 24);
    lowerLabel->setBounds (351, 45, 104, 24);
    urgencyLabel->setBounds (132, 5, 42, 12);
    urgencyValue->setBounds (169, 6, 30, 12);
    threshLabel->setBounds (203, 6, 60, 12);
    threshVal->setBounds (259, 6, 30, 12);
    toggleContinuous->setBounds (5, 40, 55, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AudioParameter::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]

    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == propertySlider)
    {
        //[UserSliderCode_propertySlider] -- add your slider handling code here..
		urgency = (float)propertySlider->getValue();
		ref->setProperty(urgency, alarmID, AudioParameter::getOrder());

		urgencyValue->setText(String(urgency,2),false);

		if (lowerTh->getComponentEffect() != NULL || upperTh->getComponentEffect() != NULL)
			propertySlider->setComponentEffect(glow);
        //[/UserSliderCode_propertySlider]
    }
    else if (sliderThatWasMoved == upperTh)
    {
        //[UserSliderCode_upperTh] -- add your slider handling code here..
		lowerTh->setComponentEffect(NULL);
		propertySlider->setComponentEffect(NULL);

		upperThMax = (float)upperTh->getMaxValue();
		upperThMin = (float)upperTh->getMinValue();

		if (upperTh->getThumbBeingDragged() >=0) {
			upperTh->setComponentEffect(glow);
			if (upperTh->getThumbBeingDragged()==1) {
				threshLabel->setText("Upper Caution:", false);			// if changing text, update in mouse dropdown menu too!!!!
				threshVal->setText(String(upperThMin, 0), false);
			}
			else {
				threshLabel->setText("Upper Emergency:", false);
				threshVal->setText(String(upperThMax, 0), false);
			}
		}

		ref->setVitalSignParams(getParamsToSend(), vitalID, AudioParameter::getOrder());
		updateStopLight();
		compareThresholds();

        //[/UserSliderCode_upperTh]
    }
    else if (sliderThatWasMoved == lowerTh)
    {
        //[UserSliderCode_lowerTh] -- add your slider handling code here..
		upperTh->setComponentEffect(NULL);
		propertySlider->setComponentEffect(NULL);

		lowerThMax = (float)lowerTh->getMaxValue();
		lowerThMin = (float)lowerTh->getMinValue();

		if (lowerTh->getThumbBeingDragged() >=0) {
			lowerTh->setComponentEffect(glow);
			if (lowerTh->getThumbBeingDragged()==1) {
				threshLabel->setText("Lower Emergency:", false);			// if changing text, update in mouse dropdown menu too!!!!
				threshVal->setText(String(lowerThMin, 0), false);
			}
			else {
				threshLabel->setText("Lower Caution:", false);
				threshVal->setText(String(lowerThMax, 0), false);
			}
		}

		ref->setVitalSignParams(getParamsToSend(), vitalID, AudioParameter::getOrder());
		updateStopLight();
		compareThresholds();
        //[/UserSliderCode_lowerTh]
    }
    else if (sliderThatWasMoved == val)
    {
        //[UserSliderCode_val] -- add your slider handling code here..
		lowerTh->setComponentEffect(NULL);			// if highlighted, return to non-highlighted
		upperTh->setComponentEffect(NULL);
		propertySlider->setComponentEffect(NULL);

		vitalVal = (float)val->getValue();
		ref->setVitalSignParams(getParamsToSend(), vitalID, AudioParameter::getOrder());
		compareThresholds();
        //[/UserSliderCode_val]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void AudioParameter::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
	threshVal->setText(T(""), false);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == AlarmSelect)
    {
        //[UserComboBoxCode_AlarmSelect] -- add your combo box handling code here..
		alarmID = AlarmSelect->getSelectedId();

		ref->init(alarmID, AudioParameter::getOrder());
		fileLabel->setText(T(""),false);
		sliderValueChanged (propertySlider);
        //[/UserComboBoxCode_AlarmSelect]
    }
    else if (comboBoxThatHasChanged == vitalSelect)
    {
        //[UserComboBoxCode_vitalSelect] -- add your combo box handling code here..
		vitalID = vitalSelect->getSelectedId();

		VitalSignParams paramsFromAudioSource = getVitalSignParams(vitalID);

		setVitalSignParams(paramsFromAudioSource);

		updateStopLight();
        //[/UserComboBoxCode_vitalSelect]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void AudioParameter::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleContinuous)
    {
        //[UserButtonCode_toggleContinuous] -- add your button handler code here..
        //[/UserButtonCode_toggleContinuous]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void AudioParameter::filesDropped (const StringArray& filenames, int mouseX, int mouseY)
{
    //[UserCode_filesDropped] -- Add your code here...
	String s;
	if (alarmID==AUDIOFILE) {		// make sure its only a sound file type
		for (int i=0; i<filenames.size(); i++) {	// grab all files dropped
			s=filenames[i];
			ref->addSoundFile(AudioParameter::getOrder(), s);
			fileLabel->setText(s,false);
			if (i==0)
				soundFile0 = s;
			else if (i==1)
				soundFile1 = s;
		}
	}
    //[/UserCode_filesDropped]
}

void AudioParameter::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
		if (e.mods.isPopupMenu()) {
		PopupMenu m;
		m.addItem(1, "Remove");
		m.addItem(2, "Set Effect Strength");
		m.addItem(3, "Set Baseline");
		m.addItem(4, "Reset");

		const int result = m.show();

		switch (result) {
		case 1:
			gui->removeObject(order);
			break;
		case 2:
			if (propertySlider->getComponentEffect() == NULL)
				AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Specify threshold...",
											"First adjust the theshold you want to set.  Then set the Urgency knob.  Finally, use the popup menu to set.");
			else{
				if (threshLabel->getText()=="Lower Emergency:")
					lowerUrgDang = (float)propertySlider->getValue();
				else if (threshLabel->getText()=="Lower Caution:")
					lowerUrgWarn = (float)propertySlider->getValue();
				else if (threshLabel->getText()=="Upper Caution:")
					upperUrgWarn = (float)propertySlider->getValue();
				else if (threshLabel->getText()=="Upper Emergency:")
					upperUrgDang = (float)propertySlider->getValue();


				ref->setVitalSignParams(getParamsToSend(), vitalID, AudioParameter::getOrder());
				AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Effect Strength Set",
					"Setting "+threshLabel->getText()+": "+threshVal->getText());

				upperTh->setComponentEffect(NULL);
				lowerTh->setComponentEffect(NULL);
				propertySlider->setComponentEffect(NULL);

			}
			break;
		case 3:
			normalUrg = (float)propertySlider->getValue();
			ref->setVitalSignParams(getParamsToSend(), vitalID, AudioParameter::getOrder());
			AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Baseline Set",
										"Baseline (normal) Urgency set to "+String(normalUrg, 3));
			break;
		case 4:
			lowerTh->setMaxValue(lowerThMax, false);
			lowerTh->setMinValue(lowerThMin);
			upperTh->setMaxValue(upperThMax, false);
			upperTh->setMinValue(upperThMin);
			compareThresholds();
			break;
		}

	}
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void AudioParameter::setVitalVal(float value) {
	//if (val != 0)
		val->setValue(value);
}

void AudioParameter::setAlarmID(int alarmID_) {
	AlarmSelect->setSelectedId(alarmID_, false);
}

void AudioParameter::setUrgency(float urg) {
	propertySlider->setValue(urg, true, true);
}

void AudioParameter::setVitalID(int id) {
	vitalSelect->setSelectedId(id, false);	// send msg to update
}

void AudioParameter::setVitalSignParams(VitalSignParams guivals) {

	normalUrg = (float)guivals.normurg;
	propertySlider->setValue(normalUrg);

	lowerTh->setRange(guivals.absmin, guivals.absmax,1);
	lowerTh->setSkewFactor(guivals.skew);
	if (guivals.lowth_warn < lowerTh->getMinValue()) {
		lowerTh->setMinValue(guivals.lowth_dang, false);
		lowerTh->setMaxValue(guivals.lowth_warn, true);
	}
	else {
		lowerTh->setMaxValue(guivals.lowth_warn, false);
		lowerTh->setMinValue(guivals.lowth_dang, true);
	}

	upperTh->setRange(guivals.absmin, guivals.absmax,1);
	upperTh->setSkewFactor(guivals.skew);
	if (guivals.uppth_warn > upperTh->getMaxValue()) {
		upperTh->setMaxValue(guivals.uppth_dang, false);
		upperTh->setMinValue(guivals.uppth_warn, true);
	}
	else {
		upperTh->setMinValue(guivals.uppth_warn, false);
		upperTh->setMaxValue(guivals.uppth_dang, true);
	}

	val->setRange(guivals.absmin, guivals.absmax,1);
	val->setSkewFactor(guivals.skew);
	val->setValue(guivals.val, true);

	lowerUrgDang = (float)guivals.lowurg_dang;
	lowerUrgWarn = (float)guivals.lowurg_warn;
	upperUrgDang = (float)guivals.uppurg_dang;
	upperUrgWarn = (float)guivals.uppurg_warn;
}

VitalSignParams AudioParameter::getParamsToSend(void) {
	VitalSignParams fromGUI;
	fromGUI.absmax = lowerTh->getMaximum();
	fromGUI.absmin = lowerTh->getMinimum();
	fromGUI.uppth_dang = upperThMax; //upperTh->getMaxValue();
	fromGUI.uppth_warn = upperThMin; //upperTh->getMinValue();
	fromGUI.lowth_dang = lowerThMin; //lowerTh->getMinValue();
	fromGUI.lowth_warn = lowerThMax; //lowerTh->getMaxValue();
	fromGUI.val = vitalVal; //val->getValue();
	fromGUI.skew = val->getSkewFactor();
	fromGUI.lowurg_warn = lowerUrgWarn;
	fromGUI.lowurg_dang = lowerUrgDang;
	fromGUI.uppurg_warn = upperUrgWarn;
	fromGUI.uppurg_dang = upperUrgDang;
	fromGUI.normurg = normalUrg;
	return fromGUI;

}

void AudioParameter::updateStopLight(void) {
	yPos = 34;
	heightBar = 8;
	widthBar = (float)(lowerTh->getWidth())-8.5f;


	startx = lowerTh->getPosition().getX()+4.f;	// danger low
	dangerLowWidth = (float)lowerTh->valueToProportionOfLength(lowerTh->getMinValue())*widthBar;

	startWarningLow = startx+dangerLowWidth;	// warning low
	warningLowWidth = (float)lowerTh->valueToProportionOfLength(lowerTh->getMaxValue())*widthBar-dangerLowWidth;

	endx = startx+widthBar;	// danger high
	dangerHighWidth = (1.f-(float)upperTh->valueToProportionOfLength(upperTh->getMaxValue()))*widthBar;
	startDangerHigh = endx-dangerHighWidth;

	warningHighWidth = (1.f-(float)upperTh->valueToProportionOfLength(upperTh->getMinValue()))*widthBar-dangerHighWidth;	// warning high
	startWarningHigh = startDangerHigh-warningHighWidth;

	startNormal = startWarningLow+warningLowWidth;	// normal
	normalWidth = startWarningHigh-startNormal;
}


VitalSignParams AudioParameter::getVitalSignParams(int vitalID_) {
	return ref->getVitalSignParams(vitalID_, AudioParameter::getOrder());
}

void AudioParameter::compareThresholds(void) {

	if (toggleContinuous->getToggleState()) {
		if ( val->getValue() >= upperTh->getMaxValue() ) {
			propertySlider->setValue(upperUrgDang);	// upper danger
		}
		else if ( val->getValue() >= upperTh->getMinValue() ) {
			float valpct = (float)(val->getValue()-upperTh->getMinValue())/(upperTh->getMaxValue()-upperTh->getMinValue());
			propertySlider->setValue(valpct*(upperUrgDang-upperUrgWarn)+upperUrgWarn);	// upper warning
		}
		else if ( val->getValue() <= lowerTh->getMinValue() ) {
			propertySlider->setValue(lowerUrgDang);	// lower danger
		}
		else if ( val->getValue() <= lowerTh->getMaxValue() ) {
			float valpct = (float)(lowerTh->getMaxValue()-val->getValue())/(lowerTh->getMaxValue()-lowerTh->getMinValue());
			propertySlider->setValue(valpct*(lowerUrgDang-lowerUrgWarn)+lowerUrgWarn);	// lower warning
		}
		else {
			propertySlider->setValue(normalUrg);	// normal
		}
	}
	else {
		if ( val->getValue() > upperTh->getMaxValue() ) {
			propertySlider->setValue(upperUrgDang);	// upper danger
		}
		else if ( val->getValue() > upperTh->getMinValue() ) {
			propertySlider->setValue(upperUrgWarn);	// upper warning
		}
		else if ( val->getValue() < lowerTh->getMinValue() ) {
			propertySlider->setValue(lowerUrgDang);	// lower danger
		}
		else if ( val->getValue() < lowerTh->getMaxValue() ) {
			propertySlider->setValue(lowerUrgWarn);	// lower warning
		}
		else {
			propertySlider->setValue(normalUrg);	// normal
		}
	}
}


void AudioParameter::textEditorTextChanged(TextEditor &editor) {
}

void AudioParameter::textEditorReturnKeyPressed(TextEditor &editor){
	gui->insertObject(order, textOrder->getText().getIntValue());
}

void AudioParameter::textEditorEscapeKeyPressed(TextEditor &editor){
	textOrder->setText (String::String(order));
}

void AudioParameter::textEditorFocusLost(TextEditor &editor){
	textOrder->setText (String::String(order));
}




int AudioParameter::getOrder(void) {
	return order;
}

void AudioParameter::setOrder(int order_) {
	order = order_;
}

void AudioParameter::timerCallback(void){
	repaint();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AudioParameter" componentName=""
                 parentClasses="public Component, public TextEditorListener, public Timer, public FileDragAndDropTarget"
                 constructorParams="int order_, SineAudioSource* ref_, GUIcomponent* const gui_"
                 variableInitialisers="order(order_)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="0" initialWidth="780"
                 initialHeight="80">
  <METHODS>
    <METHOD name="filesDropped (const StringArray&amp; filenames, int mouseX, int mouseY)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffecefff"/>
  <SLIDER name="slider" id="49d2436554bf6db6" memberName="propertySlider"
          virtualName="" explicitFocusOrder="0" pos="59 5 63 64" min="0"
          max="1" int="0.05" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="Alarm Select" id="2e91e9d52acb4243" memberName="AlarmSelect"
            virtualName="" explicitFocusOrder="0" pos="133 26 155 24" tooltip="Alarm type to sound"
            editable="0" layout="33" items="Noise&#10;Amp Mod&#10;Freq Mod&#10;Distortion&#10;Harmony&#10;Sheppard (Up)&#10;Sheppard (Dn)&#10;Pulse Width&#10;Sound File&#10;MATLAB"
            textWhenNonSelected="Alarm Type" textWhenNoItems="(no choices)"/>
  <TEXTEDITOR name="Order Box" id="268a72aabe212042" memberName="textOrder"
              virtualName="" explicitFocusOrder="0" pos="8 16 32 24" tooltip="Alarm Order"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="0" caret="1" popupmenu="1"/>
  <COMBOBOX name="Vital Select" id="1dee5b011bf7a471" memberName="vitalSelect"
            virtualName="" explicitFocusOrder="0" pos="304 26 136 24" tooltip="Vital sign to monitor"
            editable="0" layout="33" items="Heart Rate&#10;SpO2&#10;Resp Rate (AS/3)&#10;Systolic BP&#10;Diastolic BP&#10;Mean BP&#10;Temp&#10;ST elevation&#10;ETCO2&#10;Tidal Volume&#10;Minute Volume&#10;O2 Level&#10;Resp Rate (Aestiva)&#10;Max Peak Pressure&#10;FIO2&#10;FIAA&#10;pPeak-airway&#10;PEEP&#10;Min Vol Exp&#10;PCWP"
            textWhenNonSelected="Vital Sign" textWhenNoItems="(no choices)"/>
  <SLIDER name="" id="da8247590ad48e80" memberName="upperTh" virtualName=""
          explicitFocusOrder="0" pos="448 2 312 32" min="0" max="1" int="0"
          style="TwoValueHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="f60409284a6b1fb4" memberName="lowerTh" virtualName=""
          explicitFocusOrder="0" pos="448 42 312 32" min="0" max="1" int="0"
          style="TwoValueHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="File Lable" id="94494c9c7b64cf2d" memberName="fileLabel"
         virtualName="" explicitFocusOrder="0" pos="0 64 480 16" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="10.1"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="Value Slider" id="aeeaf0ddbc017135" memberName="val" virtualName=""
          explicitFocusOrder="0" pos="448 30 312 16" bkgcol="ffffff" thumbcol="ff000000"
          trackcol="ffffff" rotarysliderfill="ffffff" rotaryslideroutline="ffffff"
          min="0" max="1" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Upper Threshold" id="ad2c7f0dcec4d552" memberName="upperLabel"
         virtualName="" explicitFocusOrder="0" pos="351 4 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Upper Thresholds" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="Lower Threshold" id="be2b5a5651b58d2" memberName="lowerLabel"
         virtualName="" explicitFocusOrder="0" pos="351 45 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Lower Thresholds" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="664e9b10d749e985" memberName="urgencyLabel" virtualName=""
         explicitFocusOrder="0" pos="132 5 42 12" edTextCol="ff000000"
         edBkgCol="0" labelText="Urgency:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="0" italic="0" justification="33"/>
  <LABEL name="" id="9ba76a3b4bff8576" memberName="urgencyValue" virtualName=""
         explicitFocusOrder="0" pos="169 6 30 12" bkgCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="0" italic="0" justification="33"/>
  <LABEL name="" id="5f596ffbf2c28cde" memberName="threshLabel" virtualName=""
         explicitFocusOrder="0" pos="203 6 60 12" textCol="ff000000" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="0" italic="0" justification="33"/>
  <LABEL name="" id="eb5ad9e58174c02b" memberName="threshVal" virtualName=""
         explicitFocusOrder="0" pos="259 6 30 12" bkgCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="11"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="Continuous Sonification" id="76d12cae64035a01" memberName="toggleContinuous"
                virtualName="" explicitFocusOrder="0" pos="5 40 55 16" buttonText="Sonify"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
