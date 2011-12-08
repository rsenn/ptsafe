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

#ifndef __JUCER_HEADER_GUICOMPONENT_GUICOMPONENT_EA6A8B15__
#define __JUCER_HEADER_GUICOMPONENT_GUICOMPONENT_EA6A8B15__

//[Headers]     -- You can add your own extra header files here --

// ACOUSTIC PARAMETER VALUES
#define PULSEWIDTH_MIN 100			// lowest duration for pulse width (ms)
#define PULSEWIDTH_MAX 300			// highest duration for pulse width (ms)
#define PULSEWIDTH_SMOOTH 0.01		// amount to smooth at pulse edges (lower #: longer & smoother)
#define DISTORTION_RATIO 5			// above knee, the amount to compress
#define HARMONIC_NUMSTEPS 6			// from same note (0) to a tri-tone (6-half steps) (e.g., C-F#)
#define ALARM_TIMER 8000			// 8 sec between alarm annunciations (IEC)


// SINE AUDIO SOURCE VALUES
#define STARTING_SAT 100
#define STARTING_HR 80
#define PULSE_OX_FREQ 900			// Hz at 100%

// GUI PARAMETERS
#define GLOW_RAD 4					// radius of glow effect


#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioParameter.h"


class AudioModifier;
class AudioParameter;
class SineAudioSource;
class XmlDocumentFile;

struct VitalSignParams {
	double absmin;
	double lowth_dang;
	double lowth_warn;
	double val;
	double uppth_warn;
	double uppth_dang;
	double absmax;
	double skew;
	double lowurg_dang;
	double lowurg_warn;
	double normurg;
	double uppurg_warn;
	double uppurg_dang;
};

enum ModifierTypes {DEFAULT_ALARM, NOISE, AM, FM, DISTORTION, HARMONIC, SHEPPARD_UP, SHEPPARD_DN, GATE, AUDIOFILE, MATLAB, NUMALARMS};

enum vitalTypes {DEFAULT_VITAL, HR, SPO2, RR, SYSBP, DIABP, MNBP, TEMP, ST, /*IR,*/ ETCO2,
				TV, MV, O2LVL, RR2, MAXPP,
				/* FICO2, ETO2,*/ FIO2,/* ETN2O, FIN2O, ETAA,*/ FIAA,/* MAC, AMBP,*/ PPEAK, PEEP, /*PPLAT, TVI, TVE,
				COMP,*/ MVE, /*CO, BT,*/ PCWP, NUMVITALS};


//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
	This class is a container for AudioParameter objects that are instantiated by
	SineAudioSource, and pointed to within the audioChain.  This class also acts
	as a directory scanner, looking for new incoming patient data.

                                                                    //[/Comments]
*/
class GUIcomponent  : public Component,
                      public ChangeListener,
                      public MultiTimer,
                      public SliderListener,
                      public ButtonListener
{
public:
    //==============================================================================
    GUIcomponent ();
    ~GUIcomponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void changeListenerCallback(ChangeBroadcaster* source);
	void timerCallback(int timerID);
	int getValFromDataString(String, String);
	void insertObject(int, int);
	void removeObject(int);
	void saveSettings(void);
	XmlElement loadSettings(void);
	void loadSettings2(void);
	File getMostRecentFile(void);
	SineAudioSource *sineAudioSource;
	void grabVitalsFromDisk(File);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void mouseDown (const MouseEvent& e);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	AudioDeviceManager deviceManager;
    AudioSourcePlayer audioSourcePlayer;
	MixerAudioSource* mixerAudioSource;

	// related to directory and file info
	TimeSliceThread thread;
	DirectoryContentsList dirList;
	int numFiles;
	File currentFile;
	File nextFile;

	// timer types
	enum timerTypes {dirTimer, loadTimer, rerunTimer};

	// dynamic array of audio parameter component objects
	OwnedArray<AudioParameter> comArray;

	// file save/load
	XmlDocumentFile* settingsFile;
	VitalSignParams loadedSettings;

    //[/UserVariables]

    //==============================================================================
    AudioDeviceSelectorComponent* deviceSelector;
    Slider* slider_SineAmp;
    Label* label_SineAmp;
    HyperlinkButton* web_anesthesiology;
    Slider* slider_SineFreq;
    Label* label_SineFreq;
    Slider* slider_Rate;
    Label* label_Rate;
    Label* label_RateTh;
    ToggleButton* toggleLog;
    ToggleButton* toggleCAD;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    GUIcomponent (const GUIcomponent&);
    const GUIcomponent& operator= (const GUIcomponent&);
};


#endif   // __JUCER_HEADER_GUICOMPONENT_GUICOMPONENT_EA6A8B15__
