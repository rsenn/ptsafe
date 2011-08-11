#include "GUIcomponent.h"
#include "foolib.h"
#include "matrix.h"
#include "mclmcr.h"

/** AcousticFilter
 *  The class defines a single element of the audioChain.  It takes in information about: 1) the urgency;
 *  2) the vital sign parameters and values; and 3) the audio effect to be applied.  This information is 
 *  used to inform the processSample() method in order to apply the proper filter/synth to the pulse-ox 
 *  tone.
 */
class AcousticFilter: public MultiTimer, public Thread
{
public:
	/** AcousticFilter
     *  The constructor intializes some member variables to default values, including all of the default
	 *  alarm and threshold values.  It runs on a dedicated thread ("Timer Thread") that initializes the 
	 *  run() method, which is a highly accurate timing function.  This is to guarantee proper pulse-width
	 *  with an onset in tandem with tap() being called, and an offset specified by setProperty.
     */
	AcousticFilter():
	    Thread("Timer Thread"),
		masterLevel(0),
		masterFreq(900),
		level(0),
		GUIknee(0),
		knee(1),
		type(0),
		wasInit(false)
	{
		startThread(0);
		initVitalVals();
	}

		File lowAlarm, highAlarm, alarmToPlay;
	
	/** ~AcousticFilter
     *  The deconstructor tries to peacefully kill the thread and then calls release().
     */
	~AcousticFilter() {
						
		stopThread(5000);
		release();
	}


/** This is called by the deconstructor or when the type is changed from one modifier to another.
 */
	void release() {
		setReady(false);
		switch(type) {
			case NOISE:
				delete spitRand;
				break;
			case AM:
				delete osc;
				break;
			case HARMONIC:
				delete osc;
				stopTimer(offsetTimer);
				break;
			case SHEPPARD_UP:
			case SHEPPARD_DN:
				upperNote->~ToneGeneratorAudioSource();
				lowerNote->~ToneGeneratorAudioSource();
				break;
			case AUDIOFILE:
				stopTimer(transportTimer);
				audioFileSource->~AudioFormatReaderSource();
				break;
			case MATLAB:
				mxDestroyArray(vitalID_ptr); vitalID_ptr=NULL;
				mxDestroyArray(u_ptr); u_ptr=NULL;
				//mxDestroyArray(state_ptr); state_ptr=NULL;


				/*
				mxFree(x);
				mxFree(y);
				*/
				

				break;
		}
	}


/** Returns the current ModifierType
 */
	int getType(void){
		return type;
	}


/** Initializes when a new type is selected.
 */
	void init(int type_) {
		// if it's not the first time setting the type, then release the previous type
		if (type != DEFAULT_ALARM)		
			release();

		type = type_;

		switch(type) {
		case NOISE:
			spitRand = new Random (Time::currentTimeMillis());
			break;

		case AM:
			osc = new ToneGeneratorAudioSource ();
			osc->setFrequency(0);
			osc->setAmplitude(0);
			break;

		case HARMONIC:
			osc = new ToneGeneratorAudioSource ();
			osc->setAmplitude( 0 );
			masterShift=0;
			break;

		case SHEPPARD_UP:
		case SHEPPARD_DN:
			upperNote = new ToneGeneratorAudioSource ();
			lowerNote = new ToneGeneratorAudioSource ();
			lowerNote->setAmplitude( 0 );
			upperNote->setAmplitude( 0 );
			level = 0;
			masterFreq=900.f;
			break;

		case AUDIOFILE:
			// "plays" silence before user drops new alarm on
			loadSoundFile(File("C:\\Program Files\\PTSAFE\\Sounds\\Silence.wav"));

			break;

		case MATLAB:
			y_ptr=NULL;
			vitalID_ptr = mxCreateDoubleScalar(DEFAULT_VITAL);
			
			//state_ptr = mxCreateDoubleMatrix(1024, 1, mxREAL);


			x = (double*)mxCalloc(2560, sizeof(double));
			y = (double*)mxCalloc(2560, sizeof(double));

			break;
			
		}
	}


/** Sets a property of typeID with val [0,1].  This is set by the user with the Urgency knob.
 */
	void setProperty(double val, int typeID) {
		if (wasInit) {
			double freqHz;
			switch(typeID) {

				case MATLAB:
					if (type==MATLAB)
						u_ptr = mxCreateDoubleScalar(val);
				break;

				case GATE:
					if ( (type==GATE) | (type==HARMONIC) )
						//pulseWidth = roundDoubleToInt(val*(PULSEWIDTH_MAX-PULSEWIDTH_MIN)+PULSEWIDTH_MIN);
						pcntPW = val;
						pulseWidth = roundDoubleToInt(0.5*(pcntPW+0.5)*masterPW);
					break;

				case NOISE:
					if ((type==NOISE))
						level = val;
					break;

				case AUDIOFILE:
					if ((type==AUDIOFILE))
						if (val > 0.66)
							alarmToPlay = highAlarm;//loadSoundFile(highAlarm);
						else if (val > 0.33)
							alarmToPlay = lowAlarm; //loadSoundFile(lowAlarm);
						else
							alarmToPlay = File("C:\\Program Files\\PTSAFE\\Sounds\\Silence.wav"); //loadSoundFile(File("C:\\Program Files\\Sound GUI\\Sounds\\Silence.wav"));
					break;

				case AM:
					if (type==AM){
						osc->setFrequency((float)val*20.f);
						osc->setAmplitude((float)val);
					}
					break;

				case DISTORTION:
					if (type==DISTORTION){
						GUIknee = val;
						knee = masterLevel-val*masterLevel;
					}
					break;

				case HARMONIC:
					if (type==HARMONIC){
						masterShift = roundDoubleToInt(val*HARMONIC_NUMSTEPS);
						freqHz = masterFreq*pow(2,masterShift/12);
						osc->setFrequency(freqHz);	// shifted frequency
						wait = roundDoubleToInt( val*(PULSEWIDTH_MAX-PULSEWIDTH_MIN) );
					}
					break;

				case SHEPPARD_UP:
				case SHEPPARD_DN:
					if (type==SHEPPARD_UP || type==SHEPPARD_DN) {
						level=val;
						setAmplitude();
					}
					break;
			}
		}
	}



/** A buffer is passed in by SineAudioSource, and this function produces the output based on the
 *  type, urgency, and vital sign thresholds and value.
 */

	void processBuffer(const AudioSourceChannelInfo& bufferToFill, mxArray** state_ptr) {

		if (wasInit) {

			int numSamples = bufferToFill.numSamples;
			AudioSampleBuffer &outputBuffer=*bufferToFill.buffer;
			int startSample = bufferToFill.startSample;
			double temp;


			if (type==MATLAB) {

				for (int ch = outputBuffer.getNumChannels(); --ch >=0;) {

					x_ptr = mxCreateDoubleMatrix(numSamples, 1, mxREAL);
					y_ptr = mxCreateDoubleMatrix(numSamples, 1, mxREAL);
					


					for (int ii=0; ii<numSamples; ii++) 
						x[ii] = (double)*outputBuffer.getSampleData(ch, ii); 

					
					memcpy(mxGetPr(x_ptr), x, numSamples*sizeof(double));

					// call the implementation function
					mlfFoo(2, &y_ptr, state_ptr, x_ptr, u_ptr, *state_ptr, vitalID_ptr);

					y = mxGetPr(y_ptr);
					
					
					for (int ii=0; ii<numSamples; ii++)
						*outputBuffer.getSampleData(ch, ii) = (float)y[ii];


					mxDestroyArray(x_ptr); x_ptr=NULL;
					mxDestroyArray(y_ptr); y_ptr=NULL;

				}
					

			}
			else {
			//NOTE: could potentially break-out audioFile in addition to MATLAB for array-processing

				while (--numSamples >= 0)
				{
					for (int ch = outputBuffer.getNumChannels(); --ch >=0;) {
						float inSample = *outputBuffer.getSampleData(ch, startSample);
		///////////////////////////////////////////////////////////////////// KILLSWITCH ENGAGE

				
					switch(type) {

						case DEFAULT_ALARM:
							*outputBuffer.getSampleData(ch, startSample)=inSample;
							break;

						case GATE:
							if (level != gotoLevel) {
								if (level < gotoLevel)
									level += (1-level)*PULSEWIDTH_SMOOTH;
								else
									level *=(1-PULSEWIDTH_SMOOTH);
								if ( abs(level-gotoLevel) < PULSEWIDTH_SMOOTH)
									level = gotoLevel;
							}

							*outputBuffer.getSampleData(ch, startSample)=inSample*(float)level;
							break;

						case NOISE:
							*outputBuffer.getSampleData(ch, startSample) = inSample*(1+ (float)(level*(2*spitRand->nextDouble()-1)));
							break;

						case AM:
							*outputBuffer.getSampleData(ch, startSample) = inSample*(1+osc->getSample());
							break;

						case DISTORTION:
							if (inSample > knee)
								*outputBuffer.getSampleData(ch, startSample) = (float)(knee +(inSample-knee)/DISTORTION_RATIO);
							else
								*outputBuffer.getSampleData(ch, startSample) = inSample;
							break;

						case HARMONIC:
							*outputBuffer.getSampleData(ch, startSample)=inSample+osc->getSample();
							break;

						case SHEPPARD_UP:
						case SHEPPARD_DN:
							temp = (0.5*upperNote->getSample()+0.5*lowerNote->getSample());
							*outputBuffer.getSampleData(ch, startSample) = inSample + (float)(temp * level*masterLevel);
							break;


						case AUDIOFILE:
							//it++;	
							AudioSourceChannelInfo bufferToFill;	// create a buffer
							AudioSampleBuffer sourceBuffer (1, 1);	// make it 1 ch, 1 sample
							bufferToFill.buffer=&sourceBuffer;		
							bufferToFill.startSample=0;
							bufferToFill.numSamples=1;
					
							audioFileSource->getNextAudioBlock(bufferToFill);	// put sound-file data into bufferToFill
							*outputBuffer.getSampleData(ch, startSample) = inSample+(*bufferToFill.buffer->getSampleData(0))*(float)masterLevel; // assign to outSample

							break;

						}//switch
					

		////////////////////////////////////////////////////////////////////// END SWITCH


					} // end channel loop
					++startSample;
				} // end buffer loop (while)
			}// if/else on "is it matlab?"
		}// if wasInit		
	}// PROCESSBUFFER



/** SineAudioSource updates this function when the user changes the output level.  Important for types 
 *  that are level-dependent, such as distortion.
 */
	void setMasterLevel(double val) {
		masterLevel = val;

		switch(type) {
			
			case DISTORTION:
				setProperty(GUIknee, DISTORTION);
				break;

			case HARMONIC:
				osc->setAmplitude(0);	// assume harmony is off
				if (val > 0) {
					if(!isTimerRunning(offsetTimer) )
						startTimer(offsetTimer, wait);	// set the timer to turn it on
				}
				break;
		}
	}

/** SineAudioSource passes in information about the block size and sample rate.  Important for types that
 *  use oscillators, such as the sheppard scale or amplitude modulation.
 */
	void prepareToPlay(int samplesPerBlock_, double sampleRate_) {
		samplesPerBlock = samplesPerBlock_;
		sampleRate = sampleRate_;
		switch(type) {
			case AM:
			case HARMONIC:
				osc->prepareToPlay(samplesPerBlock, sampleRate);
				break;

			case SHEPPARD_UP:
			case SHEPPARD_DN:
				if (type==SHEPPARD_UP) {
					lowerPos = -12;
					upperPos = 0;
				}
				else {
					lowerPos = 0;
					upperPos = 12;
				}
				upperNote->prepareToPlay(samplesPerBlock, sampleRate);
				lowerNote->prepareToPlay(samplesPerBlock, sampleRate);
				break;
		}
		
	}
/** SineAudioSource passes in information about the frequency of the pulse-ox sinusoid.  Important for
 *  types that depend on freq, such as sheppard scale and harmonic offset tone.
 */
	void setMasterFrequency(double val) {
		switch(type) {
		case HARMONIC:
			masterFreq = val;		// base frequency
			break;

		case SHEPPARD_UP:
		case SHEPPARD_DN:
			f = val;
			upperNote->setFrequency( f*pow(2.f,upperPos/12.f) );
			lowerNote->setFrequency( f*pow(2.f,lowerPos/12.f) );
			break;
		}
	}

/** Sets the heart-rate.  Used only by pulse-width type to recalculate the % width of the pulse
 *  (respective to the total period between heart beats).
 */
	void setHeartRate(double val) {
		switch(type) {
		case GATE:
			masterPW = val;
			setProperty( pcntPW, GATE);
			break;
		}
	}

/** High-accuracy timer.  Should quit if threadShouldExit() is called.  Resets timer when tap() is called.
 */
	void run() {
		if (threadShouldExit())
			return;
		while(1) {
			timeNow = Time::getMillisecondCounter();
			if (threadShouldExit())
				return;
			if (tapped)
			{
				if (threadShouldExit())
					return;
				while ( (Time::getMillisecondCounter() - timeNow) < pulseWidth)
				{
					if (threadShouldExit())
						return;
				}
				gotoLevel=0;
				tapped = false;
				if (threadShouldExit())
					return;
			}
		}
	}

/** SineAudioSource calls tap() for each heart beat.  This is used as a trigger for time-dependent types
 *  such as the pulse width modifier, or for bumping up the note of a sheppard scale.
 */
	void tap(void) {
		if (wasInit) {
			switch(type){
				case GATE:
					tapped = true;
					gotoLevel=1;
					break;
				case SHEPPARD_UP:
					upperPos++;
					lowerPos++;
					if (upperPos > 11)
						upperPos = -12;
					if (lowerPos > 11)
						lowerPos = -12;
					setMasterFrequency(f);
					setAmplitude();
					break;
				case SHEPPARD_DN:
					upperPos--;
					lowerPos--;
					if (upperPos < -11)
						upperPos = 12;
					if (lowerPos < -11)
						lowerPos = 12;
					setMasterFrequency(f);
					setAmplitude();
					break;
				case HARMONIC:
					osc->setAmplitude(0);	// assume harmony is off	
					if (isTimerRunning(offsetTimer))
						stopTimer(offsetTimer);
					startTimer(offsetTimer, wait);	// set the timer to turn it on
					break;
			}
		}
	}

/** Tells other functions whether the object is ready to start processing samples yet.
 */
	void setReady(bool isReady) {
		wasInit = isReady;
	}

/** Loads a sound file from disk.  Called from drag-and-drop function.
 */
	// load file definition
	void loadSoundFile(const File& audioFile)
	{
		int readPos=0; // want to play file from same position when changing b/t med and hi urg

		if (wasInit) {	// if already declared as a different alarm type
			setReady(false);	// set not-ready so sound don't try to play while loading file
			readPos = audioFileSource->getNextReadPosition();

			audioFileSource->~AudioFormatReaderSource();	
		}
		else
			startTimer(transportTimer, ALARM_TIMER);

		AudioFormatManager formatManager;
		formatManager.registerBasicFormats();

		AudioFormatReader* reader = formatManager.createReaderFor (audioFile);
		if (reader != 0)
			audioFileSource = new AudioFormatReaderSource (reader, true);

		audioFileSource->setNextReadPosition(readPos);
		audioFileSource->prepareToPlay(samplesPerBlock, sampleRate);
		setReady(true);
	}


///////////////////////////////////////////////////////////////////////////////////////
//                     VITAL SIGN FUNCTIONS

/** If any vital sign parameters are changed on the GUI, they are passed to the AcousticFilters with 
 *  this function.  
 */
	void setVitalSignParams(VitalSignParams fromGUI, int vitalID_) {
		vitalID = vitalID_;
		vitalID_ptr = mxCreateDoubleScalar((double)vitalID);

		if (vitalID >=0 && vitalID <=20) {
			vitals[vitalID].val = fromGUI.val;
			vitals[vitalID].lowth_warn = fromGUI.lowth_warn;
			vitals[vitalID].lowth_dang = fromGUI.lowth_dang;
			vitals[vitalID].uppth_warn = fromGUI.uppth_warn;
			vitals[vitalID].uppth_dang = fromGUI.uppth_dang;
			vitals[vitalID].absmax = fromGUI.absmax;
			vitals[vitalID].absmin = fromGUI.absmin;
			vitals[vitalID].skew = fromGUI.skew;
			vitals[vitalID].lowurg_warn = fromGUI.lowurg_warn;
			vitals[vitalID].lowurg_dang = fromGUI.lowurg_dang;
			vitals[vitalID].uppurg_warn = fromGUI.uppurg_warn;
			vitals[vitalID].uppurg_dang = fromGUI.uppurg_dang;
			vitals[vitalID].normurg = fromGUI.normurg;
		}
	}

/** Get VitalSignParams for a particular vitalID.
 */
	VitalSignParams getVitalSignParams(int vitalID_){
		return vitals[vitalID_];
	}


///////////////////////////////////////////////////////////////////////////////////////

private:
///////////////////////////// FOR ACOUSTIC MODIFIERS
	// COMMON
	int type, samplesPerBlock;
	double sampleRate, level, f, masterLevel, masterFreq;
	bool wasInit, tapped;
	ToneGeneratorAudioSource *osc;
	enum timerTypes {offsetTimer, transportTimer};
	int vitalID;

	//DISTORTION
	double knee, GUIknee;

	// HARMONIC
	int wait;
	double masterShift;

	//SHEPPARD
	int upperPos, lowerPos;
	ToneGeneratorAudioSource *upperNote, *lowerNote;

	// GATE
	double gotoLevel, masterPW, pcntPW;
	unsigned int pulseWidth;
	unsigned int timeNow;

	// NOISE
	Random* spitRand;

	// AUDIO FILE
	AudioFormatReader* reader;
	AudioFormatReaderSource* audioFileSource;
	//int it;

	// MATLAB
	mxArray *x_ptr, *y_ptr, *u_ptr, *vitalID_ptr;//, *state_ptr;
	double *x, *y;


///////////////////////////// FOR VITAL SIGNS
	int vitalType;

	VitalSignParams vitals[NUMVITALS];

///////////////////////////// PRIVATE ACOUSTIC MODIFIER METHODS
	void setAmplitude()	{
		if (type==SHEPPARD_UP || type == SHEPPARD_DN) {
			double gauss[]={0.f,0.0439f,0.0756f,0.1234f,0.1915f,0.2821f,0.3947f,0.5243f,0.6615f,0.7926f,0.9019f,0.9745f,1.0000f,0.9745f,0.9019f,0.7926f,0.6615f,0.5243f,0.3947f,0.2821f,0.1915f,0.1234f,0.0756f,0.0439f,0.f};
			upperNote->setAmplitude( (float)(level*(gauss[upperPos+12])) );
			lowerNote->setAmplitude( (float)(level*(gauss[lowerPos+12])) );
		}
	}

/** Low-accuracy timers for harmonic-tone onset (offsetTimer) and file-based alarm playback (transportTimer).
 */
	void timerCallback(int timerID) {
		switch(timerID) {

		case offsetTimer:
			stopTimer(offsetTimer);
			if (masterShift==0)
				osc->setAmplitude(0);		// if enharmonic, then don't play
			else
				osc->setAmplitude((float)masterLevel/4);	
			break;

		case transportTimer:
			loadSoundFile(alarmToPlay);
			audioFileSource->setNextReadPosition(0);
			break;
		}
	}

///////////////////////////// PRIVATE VITAL SIGN METHODS
	void initVitalVals(void) {

		vitals[HR].absmin = 20;
		vitals[HR].lowth_dang = 40;
		vitals[HR].lowth_warn = 60;
		vitals[HR].val = STARTING_HR;
		vitals[HR].uppth_warn = 130;
		vitals[HR].uppth_dang = 160;
		vitals[HR].absmax = 240;
		vitals[HR].skew = 0.8f;
		vitals[HR].lowurg_dang = 1.0f;
		vitals[HR].lowurg_warn = 0.5f;
		vitals[HR].normurg = 0.0f;
		vitals[HR].uppurg_warn = 0.5f;
		vitals[HR].uppurg_dang = 1.0f;


		vitals[SPO2].absmin = 0;
		vitals[SPO2].lowth_dang = 86;
		vitals[SPO2].lowth_warn = 93;
		vitals[SPO2].val = STARTING_SAT;
		vitals[SPO2].uppth_warn = 100;
		vitals[SPO2].uppth_dang = 100;
		vitals[SPO2].absmax = 100;
		vitals[SPO2].skew = 5.f;
		vitals[SPO2].lowurg_dang = 1.0f;
		vitals[SPO2].lowurg_warn = 0.5f;
		vitals[SPO2].normurg = 0.0f;
		vitals[SPO2].uppurg_warn = 0.5f;
		vitals[SPO2].uppurg_dang = 1.0f;

		vitals[RR].absmin = 0;
		vitals[RR].lowth_dang = 6;
		vitals[RR].lowth_warn = 12;
		vitals[RR].val = 16;
		vitals[RR].uppth_warn = 30;
		vitals[RR].uppth_dang = 60;
		vitals[RR].absmax = 150;
		vitals[RR].skew = 0.8f;
		vitals[RR].lowurg_dang = 1.0f;
		vitals[RR].lowurg_warn = 0.5f;
		vitals[RR].normurg = 0.0f;
		vitals[RR].uppurg_warn = 0.5f;
		vitals[RR].uppurg_dang = 1.0f;

		vitals[SYSBP].absmin = 50;
		vitals[SYSBP].lowth_dang = 80;
		vitals[SYSBP].lowth_warn = 100;
		vitals[SYSBP].val = 120;
		vitals[SYSBP].uppth_warn = 150;
		vitals[SYSBP].uppth_dang = 180;
		vitals[SYSBP].absmax = 230;
		vitals[SYSBP].skew = 1.0f;
		vitals[SYSBP].lowurg_dang = 1.0f;
		vitals[SYSBP].lowurg_warn = 0.5f;
		vitals[SYSBP].normurg = 0.0f;
		vitals[SYSBP].uppurg_warn = 0.5f;
		vitals[SYSBP].uppurg_dang = 1.0f;

		vitals[DIABP].absmin = 35;
		vitals[DIABP].lowth_dang = 50;
		vitals[DIABP].lowth_warn = 65;
		vitals[DIABP].val = 80;
		vitals[DIABP].uppth_warn = 90;
		vitals[DIABP].uppth_dang = 105;
		vitals[DIABP].absmax = 135;
		vitals[DIABP].skew = 1.0f;
		vitals[DIABP].lowurg_dang = 1.0f;
		vitals[DIABP].lowurg_warn = 0.5f;
		vitals[DIABP].normurg = 0.0f;
		vitals[DIABP].uppurg_warn = 0.5f;
		vitals[DIABP].uppurg_dang = 1.0f;

		vitals[MNBP].absmin = 43;
		vitals[MNBP].lowth_dang = 57;
		vitals[MNBP].lowth_warn = 65;
		vitals[MNBP].val = 93;
		vitals[MNBP].uppth_warn = 120;
		vitals[MNBP].uppth_dang = 133;
		vitals[MNBP].absmax = 167;
		vitals[MNBP].skew = 1.0f;
		vitals[MNBP].lowurg_dang = 1.0f;
		vitals[MNBP].lowurg_warn = 0.5f;
		vitals[MNBP].normurg = 0.0f;
		vitals[MNBP].uppurg_warn = 0.5f;
		vitals[MNBP].uppurg_dang = 1.0f;

		vitals[TEMP].absmin = 30;
		vitals[TEMP].lowth_dang = 34;
		vitals[TEMP].lowth_warn = 35;
		vitals[TEMP].val = 37;
		vitals[TEMP].uppth_warn = 38;
		vitals[TEMP].uppth_dang = 39;
		vitals[TEMP].absmax = 44;
		vitals[TEMP].skew = 1.0f;
		vitals[TEMP].lowurg_dang = 1.0f;
		vitals[TEMP].lowurg_warn = 0.5f;
		vitals[TEMP].normurg = 0.0f;
		vitals[TEMP].uppurg_warn = 0.5f;
		vitals[TEMP].uppurg_dang = 1.0f;

		vitals[ST].absmin = 0;
		vitals[ST].lowth_dang = 0;
		vitals[ST].lowth_warn = 0;
		vitals[ST].val = 0;
		vitals[ST].uppth_warn = 1;
		vitals[ST].uppth_dang = 2;
		vitals[ST].absmax = 5;
		vitals[ST].skew = 1.0f;
		vitals[ST].lowurg_dang = 0.0f;
		vitals[ST].lowurg_warn = 0.0f;
		vitals[ST].normurg = 0.0f;
		vitals[ST].uppurg_warn = 0.5f;
		vitals[ST].uppurg_dang = 1.0f;
/*
		vitals[IR].absmin = ;
		vitals[IR].lowth_dang = ;
		vitals[IR].lowth_warn = ;
		vitals[IR].val = ;
		vitals[IR].uppth_warn = ;
		vitals[IR].uppth_dang = ;
		vitals[IR].absmax = ;
		vitals[IR].skew = 1.0f;
		vitals[IR].lowurg_dang = 0.0f;
		vitals[IR].lowurg_warn = 0.0f;
		vitals[IR].normurg = 0.0f;
		vitals[IR].uppurg_warn = 0.5f;
		vitals[IR].uppurg_dang = 1.0f;
		*/

		vitals[ETCO2].absmin = 0;
		vitals[ETCO2].lowth_dang = 22;
		vitals[ETCO2].lowth_warn = 30;
		vitals[ETCO2].val = 40;
		vitals[ETCO2].uppth_warn = 50;
		vitals[ETCO2].uppth_dang = 60;
		vitals[ETCO2].absmax = 80;
		vitals[ETCO2].skew = 1.0f;
		vitals[ETCO2].lowurg_dang = 1.0f;
		vitals[ETCO2].lowurg_warn = 0.5f;
		vitals[ETCO2].normurg = 0.0f;
		vitals[ETCO2].uppurg_warn = 0.5f;
		vitals[ETCO2].uppurg_dang = 1.0f;
		/*
		vitals[FICO2].absmin = 0;
		vitals[FICO2].lowth_dang = ;
		vitals[FICO2].lowth_warn = ;
		vitals[FICO2].val = ;
		vitals[FICO2].uppth_warn = ;
		vitals[FICO2].uppth_dang = ;
		vitals[FICO2].absmax = ;
		vitals[FICO2].skew = 1.0f;
		vitals[FICO2].lowurg_dang = 1.0f;
		vitals[FICO2].lowurg_warn = 0.5f;
		vitals[FICO2].normurg = 0.0f;
		vitals[FICO2].uppurg_warn = 0.5f;
		vitals[FICO2].uppurg_dang = 1.0f;
		*/

		vitals[FIO2].absmin = 0;
		vitals[FIO2].lowth_dang = 18;
		vitals[FIO2].lowth_warn = 19;
		vitals[FIO2].val = 21;
		vitals[FIO2].uppth_warn = 100;
		vitals[FIO2].uppth_dang = 100;
		vitals[FIO2].absmax = 100;
		vitals[FIO2].skew = 10.0f;
		vitals[FIO2].lowurg_dang = 1.0f;
		vitals[FIO2].lowurg_warn = 0.5f;
		vitals[FIO2].normurg = 0.0f;
		vitals[FIO2].uppurg_warn = 0.0f;
		vitals[FIO2].uppurg_dang = 0.0f;

		vitals[FIAA].absmin = 0;
		vitals[FIAA].lowth_dang = 0;
		vitals[FIAA].lowth_warn = 0;
		vitals[FIAA].val = 0;
		vitals[FIAA].uppth_warn = 4;
		vitals[FIAA].uppth_dang = 6;
		vitals[FIAA].absmax = 10;
		vitals[FIAA].skew = 0.9f;
		vitals[FIAA].lowurg_dang = 0.0f;
		vitals[FIAA].lowurg_warn = 0.0f;
		vitals[FIAA].normurg = 0.0f;
		vitals[FIAA].uppurg_warn = 0.5f;
		vitals[FIAA].uppurg_dang = 1.0f;

		vitals[PPEAK].absmin = -20;
		vitals[PPEAK].lowth_dang = -20;
		vitals[PPEAK].lowth_warn = -20;
		vitals[PPEAK].val = 20;
		vitals[PPEAK].uppth_warn = 30;
		vitals[PPEAK].uppth_dang = 50;
		vitals[PPEAK].absmax = 120;
		vitals[PPEAK].skew = 1.0f;
		vitals[PPEAK].lowurg_dang = 0.0f;
		vitals[PPEAK].lowurg_warn = 0.0f;
		vitals[PPEAK].normurg = 0.0f;
		vitals[PPEAK].uppurg_warn = 0.5f;
		vitals[PPEAK].uppurg_dang = 1.0f;

		vitals[PEEP].absmin = 0;
		vitals[PEEP].lowth_dang = 0;
		vitals[PEEP].lowth_warn = 0;
		vitals[PEEP].val = 0;
		vitals[PEEP].uppth_warn = 10;
		vitals[PEEP].uppth_dang = 10;
		vitals[PEEP].absmax = 30;
		vitals[PEEP].skew = 0.5f;
		vitals[PEEP].lowurg_dang = 0.0f;
		vitals[PEEP].lowurg_warn = 0.0f;
		vitals[PEEP].normurg = 0.0f;
		vitals[PEEP].uppurg_warn = 0.5f;
		vitals[PEEP].uppurg_dang = 1.0f;

		vitals[MVE].absmin = 0;
		vitals[MVE].lowth_dang = 1;
		vitals[MVE].lowth_warn = 3;
		vitals[MVE].val = 6;
		vitals[MVE].uppth_warn = 10;
		vitals[MVE].uppth_dang = 30;
		vitals[MVE].absmax = 100;
		vitals[MVE].skew = 0.4f;
		vitals[MVE].lowurg_dang = 1.0f;
		vitals[MVE].lowurg_warn = 0.5f;
		vitals[MVE].normurg = 0.0f;
		vitals[MVE].uppurg_warn = 0.25f;
		vitals[MVE].uppurg_dang = 1.0f;

		vitals[PCWP].absmin = 0;
		vitals[PCWP].lowth_dang = 2;
		vitals[PCWP].lowth_warn = 6;
		vitals[PCWP].val = 9;
		vitals[PCWP].uppth_warn = 12;
		vitals[PCWP].uppth_dang = 15;
		vitals[PCWP].absmax = 20;
		vitals[PCWP].skew = 1.0f;
		vitals[PCWP].lowurg_dang = 1.0f;
		vitals[PCWP].lowurg_warn = 0.5f;
		vitals[PCWP].normurg = 0.0f;
		vitals[PCWP].uppurg_warn = 0.5f;
		vitals[PCWP].uppurg_dang = 1.0f;
	}

};