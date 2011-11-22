/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  27 Sep 2011 1:00:15pm

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
class SineAudioSource;

#include "FileLoadSave.cpp"
class XmlDocumentFile;

//[/Headers]

#include "GUIcomponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#define T(stringLiteral)            JUCE_T(stringLiteral)
//[/MiscUserDefs]

//==============================================================================
GUIcomponent::GUIcomponent ()
    : thread("dirThread"),
      dirList(0, thread),
      deviceSelector (0),
      slider_SineAmp (0),
      label_SineAmp (0),
      web_anesthesiology (0),
      slider_SineFreq (0),
      label_SineFreq (0),
      slider_Rate (0),
      label_Rate (0),
      label_RateTh (0),
      toggleLog (0),
      toggleCAD (0)
{
    addAndMakeVisible (deviceSelector = new AudioDeviceSelectorComponent (deviceManager, 0, 0, 1, 1, false, false, false, true));

    addAndMakeVisible (slider_SineAmp = new Slider (String::empty));
    slider_SineAmp->setTooltip (L"Adjust the volume of the sine wave");
    slider_SineAmp->setRange (-42, 12, 1);
    slider_SineAmp->setSliderStyle (Slider::LinearVertical);
    slider_SineAmp->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    slider_SineAmp->setColour (Slider::thumbColourId, Colours::black);
    slider_SineAmp->setColour (Slider::rotarySliderFillColourId, Colour (0x7f000000));
    slider_SineAmp->setColour (Slider::textBoxHighlightColourId, Colour (0x40777777));
    slider_SineAmp->addListener (this);
    slider_SineAmp->setSkewFactor (2);

    addAndMakeVisible (label_SineAmp = new Label (L"Amplitude Label",
                                                  L"Amplitude"));
    label_SineAmp->setFont (Font (15.7000f, Font::plain));
    label_SineAmp->setJustificationType (Justification::centredLeft);
    label_SineAmp->setEditable (false, false, false);
    label_SineAmp->setColour (TextEditor::textColourId, Colours::black);
    label_SineAmp->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (web_anesthesiology = new HyperlinkButton (L"\xa9 UHealth Miller School of Medicine Dept Anesthesiology",
                                                                 URL (L"http://ptsafe.wordpress.com")));
    web_anesthesiology->setTooltip (L"http://ptsafe.wordpress.com");
    web_anesthesiology->setButtonText (L"\xa9 UHealth Miller School of Medicine Dept Anesthesiology");

    addAndMakeVisible (slider_SineFreq = new Slider (String::empty));
    slider_SineFreq->setTooltip (L"% O2 Saturation");
    slider_SineFreq->setRange (0, 100, 1);
    slider_SineFreq->setSliderStyle (Slider::LinearVertical);
    slider_SineFreq->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    slider_SineFreq->setColour (Slider::thumbColourId, Colours::black);
    slider_SineFreq->setColour (Slider::trackColourId, Colour (0x7fffffff));
    slider_SineFreq->setColour (Slider::rotarySliderFillColourId, Colour (0x7f5056c6));
    slider_SineFreq->setColour (Slider::textBoxHighlightColourId, Colour (0x40757575));
    slider_SineFreq->addListener (this);
    slider_SineFreq->setSkewFactor (2);

    addAndMakeVisible (label_SineFreq = new Label (L"Frequency Label",
                                                   L"Saturation"));
    label_SineFreq->setFont (Font (15.0000f, Font::plain));
    label_SineFreq->setJustificationType (Justification::centredLeft);
    label_SineFreq->setEditable (false, false, false);
    label_SineFreq->setColour (TextEditor::textColourId, Colours::black);
    label_SineFreq->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (slider_Rate = new Slider (String::empty));
    slider_Rate->setTooltip (L"Beats per minute");
    slider_Rate->setRange (30, 240, 1);
    slider_Rate->setSliderStyle (Slider::LinearVertical);
    slider_Rate->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    slider_Rate->setColour (Slider::thumbColourId, Colours::black);
    slider_Rate->setColour (Slider::trackColourId, Colour (0x7fffffff));
    slider_Rate->setColour (Slider::rotarySliderFillColourId, Colour (0x7f5056c6));
    slider_Rate->setColour (Slider::textBoxHighlightColourId, Colour (0x40757575));
    slider_Rate->addListener (this);

    addAndMakeVisible (label_Rate = new Label (L"Rate Label",
                                               L"Heart Rate"));
    label_Rate->setFont (Font (15.0000f, Font::plain));
    label_Rate->setJustificationType (Justification::centredLeft);
    label_Rate->setEditable (false, false, false);
    label_Rate->setColour (TextEditor::textColourId, Colours::black);
    label_Rate->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (label_RateTh = new Label (String::empty,
                                                 L"HR threshold"));
    label_RateTh->setFont (Font (15.0000f, Font::plain));
    label_RateTh->setJustificationType (Justification::centredLeft);
    label_RateTh->setEditable (false, false, false);
    label_RateTh->setColour (TextEditor::textColourId, Colours::black);
    label_RateTh->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (toggleLog = new ToggleButton (L"Toggle Log"));
    toggleLog->setButtonText (L"Log");
    toggleLog->addListener (this);

    addAndMakeVisible (toggleCAD = new ToggleButton (L"Toggle CAD"));
    toggleCAD->setButtonText (L"CAD");
    toggleCAD->addListener (this);


    //[UserPreSize]

	// Init slider values
	slider_SineFreq->setValue(STARTING_SAT);
	slider_Rate->setValue(STARTING_HR);

    //[/UserPreSize]

    setSize (800, 1800);


    //[Constructor] You can add your own custom stuff here..
	deviceManager.initialise (0, 1, 0, true, String::empty, 0);

	mixerAudioSource = new MixerAudioSource ();
    sineAudioSource = new SineAudioSource ();
	mixerAudioSource->addInputSource(sineAudioSource, false);
    audioSourcePlayer.setSource (mixerAudioSource);

    deviceManager.addAudioCallback (&audioSourcePlayer);
	deviceManager.addChangeListener(this);

	// setup the file save/load elements
	settingsFile = new XmlDocumentFile();

	// setup the directory watcher
	numFiles = 0;
	File folder = File::getSpecialLocation (File::userDocumentsDirectory).getChildFile("PTSAFE/Data/");
	dirList.setDirectory(folder, false, true);	// don't watch folders, do watch files
	dirList.addChangeListener(this);	// register our changeListener callback
	thread.startThread (0);		// priority: lo 0..[3]....10 hi
	currentFile = getMostRecentFile();
	startTimer(dirTimer, 100);

	// turn on the CAD and turn off the log
	toggleCAD->setToggleState(true, true);
	toggleLog->setToggleState(false, true);

    //[/Constructor]
}

GUIcomponent::~GUIcomponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	mixerAudioSource->removeAllInputs();
	audioSourcePlayer.setSource (0);
    deviceManager.removeAudioCallback (&audioSourcePlayer);
    delete sineAudioSource;
	delete mixerAudioSource;
	delete settingsFile;
	stopTimer(dirTimer);
	stopTimer(loadTimer);
	stopTimer(rerunTimer);
    //[/Destructor_pre]

    deleteAndZero (deviceSelector);
    deleteAndZero (slider_SineAmp);
    deleteAndZero (label_SineAmp);
    deleteAndZero (web_anesthesiology);
    deleteAndZero (slider_SineFreq);
    deleteAndZero (label_SineFreq);
    deleteAndZero (slider_Rate);
    deleteAndZero (label_Rate);
    deleteAndZero (label_RateTh);
    deleteAndZero (toggleLog);
    deleteAndZero (toggleCAD);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GUIcomponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colour (0xff888888));
    g.fillRect (8, 4, 776, 180);

    g.setColour (Colour (0xff4a4a4a));
    g.drawRect (8, 4, 776, 180, 3);

    g.setColour (Colour (0xffe4e4e4));
    g.fillRect (0, 192, 800, 1600);

    g.setColour (Colour (0xffcacaca));
    g.drawRect (0, 192, 800, 1600, 3);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GUIcomponent::resized()
{
    deviceSelector->setBounds (272, 8, 498, 168);
    slider_SineAmp->setBounds (27, 32, 56, 144);
    label_SineAmp->setBounds ((27) + -8, (32) + -24, 72, 24);
    web_anesthesiology->setBounds (440, 165, 301, 18);
    slider_SineFreq->setBounds ((27) + 75, 32, 72, 136);
    label_SineFreq->setBounds (((27) + 75) + 36 - ((72) / 2), (32) + -24, 72, 31);
    slider_Rate->setBounds ((27) + 165, 32, 72, 136);
    label_Rate->setBounds (((27) + 165) + 42 - ((83) / 2), (32) + -24, 83, 31);
    label_RateTh->setBounds (24 - ((80) / 2), -24, 80, 31);
    toggleLog->setBounds (((27) + 165) + 136, 128, 47, 24);
    toggleCAD->setBounds (((27) + 165) + 136, 152, 47, 24);
    //[UserResized] Add your own custom resize handling here..

	for (int i=0; i<comArray.size(); i++)
		comArray[i]->setBounds(10, 208+i*(comArray.getFirst()->getHeight()+5), 780, 80);

    //[/UserResized]
}

void GUIcomponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider_SineAmp)
    {
        //[UserSliderCode_slider_SineAmp] -- add your slider handling code here..
		sineAudioSource->setLevel(slider_SineAmp->getValue());

        //[/UserSliderCode_slider_SineAmp]
    }
    else if (sliderThatWasMoved == slider_SineFreq)
    {
        //[UserSliderCode_slider_SineFreq] -- add your slider handling code here..
		sineAudioSource->setFrequency(slider_SineFreq->getValue());
		for (int i=0; i<comArray.size(); i++) {
			if ( comArray[i]->getVitalID() == SPO2 )
				comArray[i]->setVitalVal((float)slider_SineFreq->getValue());
		}
        //[/UserSliderCode_slider_SineFreq]
    }
    else if (sliderThatWasMoved == slider_Rate)
    {
        //[UserSliderCode_slider_Rate] -- add your slider handling code here..
		sineAudioSource->setRate(slider_Rate->getValue());
		for (int i=0; i<comArray.size(); i++) {
			if ( comArray[i]->getVitalID() == HR )
				comArray[i]->setVitalVal((float)slider_Rate->getValue());
		}

        //[/UserSliderCode_slider_Rate]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void GUIcomponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleLog)
    {
        //[UserButtonCode_toggleLog] -- add your button handler code here..
        //[/UserButtonCode_toggleLog]
    }
    else if (buttonThatWasClicked == toggleCAD)
    {
        //[UserButtonCode_toggleCAD] -- add your button handler code here..
		sineAudioSource->toggleCAD(toggleCAD->getToggleState());
        //[/UserButtonCode_toggleCAD]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void GUIcomponent::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	if (e.mods.isPopupMenu()) {
		PopupMenu m;
		m.addItem(1, "Add new monitor");
		m.addItem(2, "Save Settings");
		m.addItem(3, "Load Settings");
		m.addItem(4, "Re-run case");
		m.addItem(5, "Live monitoring");

		const int result = m.show();

		switch (result) {
		case 1:
			{// Add new monitor
			// add a pointer to the new component
			comArray.add(new AudioParameter(comArray.size(), sineAudioSource, this));
			// make it visible
			addAndMakeVisible (comArray.getLast());
			resized();
			}
			break;
		case 2:
			{// Save settings
			saveSettings();
			}
			break;
		case 3:
			{// Load settings
			loadSettings();
			resized();
			startTimer(loadTimer, 50);
			}
			break;
		case 4:
			{// Re-run case
			// stop the live monitor
			stopTimer(dirTimer);

			// ask the user to select a starting-off file
			WildcardFileFilter wildcardFilter ("*.csv", String::empty, "PT-SAFE log files");
			File lookIn = File::getSpecialLocation (File::userDocumentsDirectory).getChildFile("PTSAFE/Data/");
			FileBrowserComponent browser (FileBrowserComponent::canSelectFiles|FileBrowserComponent::openMode,
										  lookIn, &wildcardFilter, nullptr);
			FileChooserDialogBox dialogBox("Open a PT-SAFE log file", "Select a starting file...", browser,
											false, Colours::lightgrey);
			if (dialogBox.show())
			{
				currentFile = browser.getSelectedFile(0);
				grabVitalsFromDisk(currentFile);
				nextFile = currentFile;
				startTimer(rerunTimer, 1000);
			}

			}

			break;

		case 5: // Live monitoring
			currentFile = getMostRecentFile();
			grabVitalsFromDisk(currentFile);
			stopTimer(rerunTimer);
			startTimer(dirTimer, 100);
			break;
		}
	}
    //[/UserCode_mouseDown]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void GUIcomponent::saveSettings(void) {
	for (int i=0; i<comArray.size(); i++) {// send over all of the components individually
		if (comArray[i]->getVitalID() >= 0 && comArray[i]->getVitalID() < 20)
			settingsFile->saveXML(i, comArray[i]);
	}
	settingsFile->saveAsInteractive(true);			// then send a save command ... FBD takes care of removing old data

}

void GUIcomponent::loadSettings2() {
	XmlElement xml("VITALS");
	xml = settingsFile->loadLastXmlElement();

	for (int i=0; i<xml.getNumChildElements(); i++) {
		XmlElement thisElem (*xml.getChildElement(i));

		// build up a VitalSignParams struct
		loadedSettings.absmax = (float)thisElem.getDoubleAttribute("absMax");
		loadedSettings.absmin = (float)thisElem.getDoubleAttribute("absMin");
		loadedSettings.uppth_dang = (float)thisElem.getDoubleAttribute("upperThMax");
		loadedSettings.uppth_warn = (float)thisElem.getDoubleAttribute("upperThMin");
		loadedSettings.lowth_dang = (float)thisElem.getDoubleAttribute("lowerThMin");
		loadedSettings.lowth_warn = (float)thisElem.getDoubleAttribute("lowerThMax");
		loadedSettings.skew = (float)thisElem.getDoubleAttribute("skew");
		loadedSettings.val = (float)thisElem.getDoubleAttribute("vitalVal");
		loadedSettings.lowurg_dang = (float)thisElem.getDoubleAttribute("lowerUrgDang");
		loadedSettings.lowurg_warn = (float)thisElem.getDoubleAttribute("lowerUrgWarn");
		loadedSettings.uppurg_warn = (float)thisElem.getDoubleAttribute("upperUrgWarn");
		loadedSettings.uppurg_dang = (float)thisElem.getDoubleAttribute("upperUrgDang");
		loadedSettings.normurg = (float)thisElem.getDoubleAttribute("normalUrg");

		comArray[i]->setVitalSignParams(loadedSettings);
	}
	resized();
}

XmlElement GUIcomponent::loadSettings(void) {
	XmlElement xml("VITALS");
	xml = settingsFile->loadXML();
	comArray.clear(true);

	int numChildren = xml.getNumChildElements();

	for (int i=0; i<numChildren; i++){
		comArray.add(new AudioParameter(i, sineAudioSource, this));
		// make it visible
		addAndMakeVisible (comArray.getLast());

		XmlElement thisElem (*xml.getChildElement(i));

		comArray[i]->setAlarmID(thisElem.getIntAttribute("alarmID"));
		comArray[i]->setVitalID(thisElem.getIntAttribute("vitalID"));
		comArray[i]->setUrgency((float)thisElem.getDoubleAttribute("urgency"));

		if (comArray[i]->getAlarmID() == AUDIOFILE) { // if the alarm is an audiofile
			StringArray soundFile0 (thisElem.getStringAttribute("soundFile0"));	// create a string from the XML attribute
			StringArray soundFile1 (thisElem.getStringAttribute("soundFile1"));
			StringArray tempArray;
			tempArray.addArray(soundFile0);
			tempArray.addArray(soundFile1);
			comArray[i]->filesDropped (tempArray, 0, 0);	// do a "fake" drag and drop of the file onto the GUI
		}

		thisElem.removeAllAttributes();
	}
	return xml;
}


void GUIcomponent::insertObject(int from, int to) {
	if (to != from) {

		comArray.insert(to, comArray.removeAndReturn(from));

		sineAudioSource->insertObject(from, to);

		for (int i=0; i<comArray.size(); i++)
			comArray[i]->setOrder(i);

		resized();
	}
}

void GUIcomponent::removeObject(int obj) {

	comArray.remove(obj);
	sineAudioSource->removeObject(obj);

	for (int i=0; i<comArray.size(); i++)
		comArray[i]->setOrder(i);

	resized();
}

void GUIcomponent::timerCallback(int timerID)
{
	if (timerID==dirTimer) {
		dirList.refresh();
	}

	if (timerID==loadTimer) {
		loadSettings2();
		stopTimer(loadTimer);
	}

	if (timerID==rerunTimer) {
		File currentDir = currentFile.getParentDirectory();
		String fileName = nextFile.getFileNameWithoutExtension();
		int64 fileNumber = fileName.getLargeIntValue();

		String nextFileName = String(fileNumber+1);
		nextFileName+=T(".csv");
		nextFile = currentDir.getChildFile(nextFileName);
		if (nextFile.exists())
			grabVitalsFromDisk(nextFile);
	}

}

File GUIcomponent::getMostRecentFile(void)
{
	DirectoryIterator iter (dirList.getDirectory(), false, "*.csv");
	File mostRecentFile;

	while (iter.next()) {
		if (iter.getFile().getFileNameWithoutExtension().compare(mostRecentFile.getFileName()) )
			mostRecentFile = iter.getFile();
	}

	return mostRecentFile;
}
void GUIcomponent::changeListenerCallback(ChangeBroadcaster* source)
	// when the directory is updated
{
	File temp = getMostRecentFile();

	String a = currentFile.getFileNameWithoutExtension();
	String b = temp.getFileNameWithoutExtension();

	if (a.compare(b)<0 )
	{
		// delete older currentFile
		if (!toggleLog->getToggleState())
			currentFile.deleteFile();

		grabVitalsFromDisk(temp);
	}
}


void GUIcomponent::grabVitalsFromDisk(File newFile)
{
		// open the most recent file
		currentFile = newFile;
		String fileData = currentFile.loadFileAsString();

		// get all the values and set appropriate
		slider_SineFreq->setValue(getValFromDataString(fileData, T("sat")));
		slider_Rate->setValue(getValFromDataString(fileData, T("hr")));

		for (int i=0; i<comArray.size(); i++) {
			int id = comArray[i]->getVitalID();
			switch (id) {
			case HR:	// heart rate
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("hr")));
				break;
			case SPO2:	// oxygen saturation
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("sat")));
				break;
			case RR:	// respiratory rate
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("rr")));
				break;
			case SYSBP:	// systolic blood pressure
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("sys")));
				break;
			case DIABP:	// diastolic blood pressure
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("dia")));
				break;
			case MNBP:	// mean blood pressure
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("mean")));
				break;
			case TEMP:	// body temperature
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("temp")));
				break;
			case ST:	// EKG ST-segment elevation
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("st")));
				break;
			case TV: // tidal volume from aestiva
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("tv")));
				break;
			case MV: // minute volume
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("mv")));
				break;
			case O2LVL: // oxygen level
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("o2lvl")));
				break;
			case RR2: // respiratory rate from aestiva
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("rr2")));
				break;
			case MAXPP: // maximum peak pressure (aestiva)
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("maxpp")));
				break;
				/*
			case IR:	// infrared amplitude
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("ir")));
				break;
				*/
			case ETCO2:	// end tidal CO2
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("etco2")));
				break;
				/*
			case FICO2:	// fractional inspired CO2
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("fico2")));
				break;
			case ETO2:	// end tidal O2
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("eto2")));
				break;
				*/
			case FIO2:	// fractional inspired O2
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("fio2")));
				break;
				/*
			case ETN2O:	// end tidal N2O
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("etn2o")));
				break;
			case FIN2O:	// fractional inspired N2O
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("fin2o")));
				break;
			case ETAA:	// end tidal anesthetic agent
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("etaa")));
				break;
				*/
			case FIAA:	// fractional inspired anesthetic agent
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("fiaa")));
				break;
				/*
			case MAC:	// minimum alveolar concentration
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("mac")));
				break;
			case AMBP:	// ambient pressure
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("ambp")));
				break;
				*/
			case PPEAK:// peak airway pressure
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("ppeak")));
				break;
			case PEEP:// positive end expiratory pressure
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("peep")));
				break;
				/*
			case PPLAT:// plateau pressure
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("pplat")));
				break;
			case TVI:	// tidal volume inspiration
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("tvi")));
				break;
			case TVE:	// tidal volume expiration
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("tve")));
				break;
			case COMP:	// compliance
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("com")));
				break;
				*/
			case MVE:	// minute volume expiration
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("mve")));
				break;
				/*
			case CO:	// cardiac output
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("co")));
				break;
			case BT:	// blood temperature
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("bt")));
				break;
				*/
			case PCWP:	// pulmonary capillary wedge pressure
				comArray[i]->setVitalVal((float)getValFromDataString(fileData, T("pcwp")));
				break;
			}
		}
}


int GUIcomponent::getValFromDataString(String data, String id) {
	int indexParam, indexComma1, indexComma2, newVal;
	// parse
	indexParam = data.indexOf(0, id);	// find appropriate parameter
	indexComma1 = data.indexOf(indexParam, T(",")); // find comma after id (eg., ...hr, 71.0, rr, 6.5, ....)
	indexComma2 = data.indexOf(indexComma1+1, T(",")); // find the comma after the id value
	String substring = data.substring(indexComma1+1, indexComma2);		// read b/t the commas
	newVal = substring.getIntValue();
	return newVal;
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GUIcomponent" componentName=""
                 parentClasses="public Component, public ChangeListener, public MultiTimer"
                 constructorParams="" variableInitialisers="thread(&quot;dirThread&quot;),&#10;dirList(0, thread)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="800" initialHeight="1800">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="8 4 776 180" fill="solid: ff888888" hasStroke="1" stroke="3.29999995, mitered, butt"
          strokeColour="solid: ff4a4a4a"/>
    <RECT pos="0 192 800 1600" fill="solid: ffe4e4e4" hasStroke="1" stroke="3.29999995, mitered, butt"
          strokeColour="solid: ffcacaca"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="" id="3c824ba4c7549c13" memberName="deviceSelector" virtualName=""
                    explicitFocusOrder="0" pos="272 8 498 168" class="AudioDeviceSelectorComponent"
                    params="deviceManager, 0, 0, 1, 1, false, false, false, true"/>
  <SLIDER name="" id="d0de66c6c0fab642" memberName="slider_SineAmp" virtualName=""
          explicitFocusOrder="0" pos="27 32 56 144" tooltip="Adjust the volume of the sine wave"
          thumbcol="ff000000" rotarysliderfill="7f000000" textboxhighlight="40777777"
          min="-42" max="12" int="1" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="2"/>
  <LABEL name="Amplitude Label" id="c287df4cbf014685" memberName="label_SineAmp"
         virtualName="" explicitFocusOrder="0" pos="-8 -24 72 24" posRelativeX="d0de66c6c0fab642"
         posRelativeY="d0de66c6c0fab642" edTextCol="ff000000" edBkgCol="0"
         labelText="Amplitude" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.7"
         bold="0" italic="0" justification="33"/>
  <HYPERLINKBUTTON name="Anesthesiology Link" id="e9bae957461270e0" memberName="web_anesthesiology"
                   virtualName="" explicitFocusOrder="0" pos="440 165 301 18" tooltip="http://ptsafe.wordpress.com"
                   buttonText="&#169; UHealth Miller School of Medicine Dept Anesthesiology"
                   connectedEdges="0" needsCallback="0" radioGroupId="0" url="http://ptsafe.wordpress.com"/>
  <SLIDER name="" id="76f56ba8346165c2" memberName="slider_SineFreq" virtualName=""
          explicitFocusOrder="0" pos="75 32 72 136" posRelativeX="d0de66c6c0fab642"
          tooltip="% O2 Saturation" thumbcol="ff000000" trackcol="7fffffff"
          rotarysliderfill="7f5056c6" textboxhighlight="40757575" min="0"
          max="100" int="1" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="2"/>
  <LABEL name="Frequency Label" id="aa310c1b51b0566f" memberName="label_SineFreq"
         virtualName="" explicitFocusOrder="0" pos="36c -24 72 31" posRelativeX="76f56ba8346165c2"
         posRelativeY="76f56ba8346165c2" edTextCol="ff000000" edBkgCol="0"
         labelText="Saturation" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="" id="200f14d087a1fc8e" memberName="slider_Rate" virtualName=""
          explicitFocusOrder="0" pos="165 32 72 136" posRelativeX="d0de66c6c0fab642"
          tooltip="Beats per minute" thumbcol="ff000000" trackcol="7fffffff"
          rotarysliderfill="7f5056c6" textboxhighlight="40757575" min="30"
          max="240" int="1" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Rate Label" id="4a76f84050bc6cd6" memberName="label_Rate"
         virtualName="" explicitFocusOrder="0" pos="41.5c -24 83 31" posRelativeX="200f14d087a1fc8e"
         posRelativeY="200f14d087a1fc8e" edTextCol="ff000000" edBkgCol="0"
         labelText="Heart Rate" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="" id="96a1f749c63e8595" memberName="label_RateTh" virtualName=""
         explicitFocusOrder="0" pos="24c -24 80 31" posRelativeX="cbee6b285ea4613d"
         posRelativeY="cbee6b285ea4613d" edTextCol="ff000000" edBkgCol="0"
         labelText="HR threshold" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="Toggle Log" id="c3e95e7b6a724c01" memberName="toggleLog"
                virtualName="" explicitFocusOrder="0" pos="136 128 47 24" posRelativeX="200f14d087a1fc8e"
                buttonText="Log" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="Toggle CAD" id="34f07c5369c09bf9" memberName="toggleCAD"
                virtualName="" explicitFocusOrder="0" pos="136 152 47 24" posRelativeX="200f14d087a1fc8e"
                buttonText="CAD" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
