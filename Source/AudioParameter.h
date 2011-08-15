/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  15 Mar 2011 11:35:15am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_AUDIOPARAMETER_AUDIOPARAMETER_E471E71F__
#define __JUCER_HEADER_AUDIOPARAMETER_AUDIOPARAMETER_E471E71F__

//[Headers]     -- You can add your own extra header files here --
#include "GUIcomponent.h"
class SineAudioSource;
class GUIcomponent;
struct VitalSignParams;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    This class is a component that has objects created and/or destroyed at run-
	time.  A parameter is a self-contained GUI element as well as controller
	(view-controller class) that interfaces with the sound GUI to handle graphics
	and the SineAudioSource to handle audio flow.
                                                                    //[/Comments]
*/
class AudioParameter  : public Component,
                        public TextEditorListener,
                        public Timer,
                        public FileDragAndDropTarget,
                        public SliderListener,
                        public ComboBoxListener
{
public:
    //==============================================================================
    AudioParameter (int order_, SineAudioSource* ref_, GUIcomponent* const gui_);
    ~AudioParameter();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback(void);

	void textEditorTextChanged(TextEditor &editor);
	void textEditorReturnKeyPressed(TextEditor &editor);
	void textEditorEscapeKeyPressed(TextEditor &editor);
	void textEditorFocusLost(TextEditor &editor);

	bool isInterestedInFileDrag(const StringArray&){return true;};
	void fileDragEnter(const StringArray&, int, int){};
	void fileDragMove(const StringArray&, int, int){};
	void fileDragExit(const StringArray&){};

	void updateStopLight(void);
	void compareThresholds(void);
	VitalSignParams getParamsToSend(void);

	void setVitalSignParams(VitalSignParams);
	void setOrder(int);
	void setVitalVal(float);
	void setAlarmID(int);
	void setUrgency(float);
	void setVitalID(int);

	int getOrder(void);
	float getUrgency(void) {return urgency;};
	int getAlarmID(void) {return alarmID;};
	int getVitalID(void) {return vitalID;};
	VitalSignParams getVitalSignParams(int);


	String getSoundFile0(void) {return soundFile0;};
	String getSoundFile1(void) {return soundFile1;};

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY);
    void mouseDown (const MouseEvent& e);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	// internal variables that other objects may need to know about
	int order;
	float urgency, upperThMin, upperThMax, lowerThMin, lowerThMax, vitalVal;
	float lowerUrgDang, lowerUrgWarn, upperUrgWarn, upperUrgDang, normalUrg;
	int alarmID, vitalID;

	// references to calling objects
	SineAudioSource* ref;
	GUIcomponent* gui;

	// glow effects:
	GlowEffect* glow;

	// for stoplight
	float startx, widthBar, endx, heightBar, yPos;
	float dangerLowWidth, warningLowWidth, warningHighWidth, dangerHighWidth, normalWidth;
	float startWarningLow, startNormal, startDangerHigh, startWarningHigh;

	// sound file
	String soundFile0, soundFile1;

    //[/UserVariables]

    //==============================================================================
    Slider* propertySlider;
    ComboBox* AlarmSelect;
    TextEditor* textOrder;
    ComboBox* vitalSelect;
    Slider* upperTh;
    Slider* lowerTh;
    Label* fileLabel;
    Slider* val;
    Label* upperLabel;
    Label* lowerLabel;
    Label* urgencyLabel;
    Label* urgencyValue;
    Label* threshLabel;
    Label* threshVal;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    AudioParameter (const AudioParameter&);
    const AudioParameter& operator= (const AudioParameter&);
};


#endif   // __JUCER_HEADER_AUDIOPARAMETER_AUDIOPARAMETER_E471E71F__
