#include "GUIcomponent.h"
#include "AcousticModifiers.cpp"
#define T(stringLiteral)            JUCE_T(stringLiteral)

/** SineAudioSource
 *  The main goals of this class are to 1) produce an appropriate sinusoid that corresponds in frequency to 
 *  the nominal SpO2 level, and corresponds in amplitude to the user-generated level; 2) broadcasts a pulse
 *  that corresponds to the nominal heart-rate (in beats per minute); 3) apply the audio effects passed in 
 *  from the GUI to the signal in a chained fasion.  
 */
class SineAudioSource  : public AudioSource, public Thread
{
public:

	/** PulseOximeter
     *  This struct has 4 values associated strictly with the pulse-oximeter continuous auditory display, 
	 *  namely, [freqRad] the frequency (as provided by SpO2) in radians, [phase] the current phase of 
	 *  the output sinusoid, [level] the full-scale intensity of the sinusoid, and [period]  the total
	 *  time between heart beats (as provided by HR).  The member variable pulseOx holds this information.
     */
	struct PulseOximeter {
		double freqRad;		// freq in radians
		double phase;		// current phase
		double level;		// intensity
		double period;		// total time on and off before next pulse
	} pulseOx;

	/** SineAudioSource
	 *  Nothing is needed for the constructor.  The level is initialized to 0 to prevent DC-pulses. 
	 *  (called from GUIcomponent)
	 */
    SineAudioSource (): Thread("SineAudioSource Thread")
	{	
		osc = new ToneGeneratorAudioSource ();
		startThread(8);
		setLevel(0); 	

		mclInitializeApplication(NULL,0);
		foolibInitialize();
		state = mxCreateDoubleMatrix(1024, 1, mxREAL);
	}

	/** This is called when a heartRate pulse begins.  It informs all elements of the audioChain by 
	 *  sending them a tap() command.
	 */
	void run() {
		timeNow = 0;
		while (!threadShouldExit()) {
			timeNow = Time::getMillisecondCounter();
			while ( (Time::getMillisecondCounter() - timeNow) < (unsigned int)roundDoubleToInt(pulseOx.period))
			{}

			for (int i=0; i <audioChain.size(); i++)
				audioChain[i]->tap();
		}
		return;
	}


	/** This adds a new AcousticFilter to the audioChain.  It is called when the user creates a new
	 *  monitoring component in the GUI (called from AudioParameter).
	 */
	void addParam(void) {
		audioChain.add(new AcousticFilter());
	}
	


	/** This is called by an element of audioChain when a user selects a new (non-default) alarm type.
	 *  It prepares the element for processing audio (called from AudioParameter).
	 */
	void init(int type, int order) {
		audioChain[order]->init(type);
		audioChain[order]->prepareToPlay(1024, sampleRate);
		setFrequency (SAT);
		audioChain[order]->setMasterLevel(pulseOx.level);
		audioChain[order]->setReady(true);
	}


	/** This is a call to an element of the audioChain to request the VitalSignParams associated with the
	 *  a particular vitalID.  This is normally called when the monitored vital sign is changed, and the 
	 *  GUI must reflect the new thresholds, etc. (called from AudioParameter).
	 */
	VitalSignParams getVitalSignParams(int vitalID, int order) {
		VitalSignParams temp = audioChain[order]->getVitalSignParams(vitalID);
		return temp;
	}


	/** This is called by an element of the audioChain to update the VitalSignParams associated with the
	 *  a particular vitalID.  This is normally called when the user makes a change to the GUI.  The
	 *  acoustic modifier for this element must be updated to reflect the new thresholds, etc. (called
	 *  from AudioParameter).
	 */
	void setVitalSignParams(VitalSignParams fromGUI, int vitalID, int order) {
		audioChain[order]->setVitalSignParams(fromGUI, vitalID);
	}


	/** This loads a sound file located at path s into an element of the audioChain (called from 
	 *  AudioParameter).
	 */
	void addSoundFile(int order, String s) {
				
		if (s.containsIgnoreCase(T("med")) | s.containsIgnoreCase(T("low")) | s.containsIgnoreCase(T("caution")) | s.containsIgnoreCase(T("warn"))) {	// medium urgency
			audioChain[order]->lowAlarm = s;
		}
		else if (s.containsIgnoreCase(T("high")) | s.containsIgnoreCase(T("emergency")) | s.containsIgnoreCase(T("danger")) | s.containsIgnoreCase(T("upper")) ) {	// high urgency
			audioChain[order]->highAlarm = s;
		}

	}


	/** This switches the order of an element in audioChain from one location to another. (called from 
	 *  GUIcomponent).
	 */
	void insertObject(int from, int to) {
		if (to != from)
			audioChain.insert(to, audioChain.removeAndReturn(from));
	}
	

	/** This removes an element from the audioChain. (called from GUIcomponent).
	 */
	void removeObject(int obj) {
		audioChain.remove(obj);
	}

	/** This sets the pulse-ox CAD within or without the processing chain.
	 */
	void toggleCAD(bool isOn) {
		cad = isOn;
	}

	/** This returns the status of the pulse-ox CAD w.r.t. its inclusion in the Fx chain
	 */
	bool getCAD(void){
		return cad;
	}


	/** This is called from an element (order) of audioChain to set a property (type) to a particular 
	 *  value (val).  Called from AudioParameter when the user changes the Urgency knob.
	 */
	void setProperty(double val, int type, int order) {
		audioChain[order]->setHeartRate(pulseOx.period);
		audioChain[order]->setProperty(val, type);
	}


	/** This is an overridden JUCE function that handles basic information about the expected audio 
	 *  buffer size and sample rate, and passes the same information to each of the elements in the 
	 *  audioChain
	 */
	void prepareToPlay (int samplesPerBlockExpected, double sampleRate_)
    {
		// get the sample rate
		sampleRate = sampleRate_;

		for (int i=0; i <audioChain.size(); i++)
			audioChain[i]->prepareToPlay(samplesPerBlockExpected, sampleRate);

		// reset the running sinusoid
		pulseOx.phase = 0.0;

		// if sample rate changes, we need to recalculate frequency (which is sampleRate-dependent)
		setFrequency(SAT);		// derive from value of O2-Saturation

		osc->prepareToPlay(samplesPerBlockExpected, sampleRate);
    }

	void releaseResources() {}


	/** Sets the amplitude of the pulse-oximeter sinusoid, then send level info to all audioChain elements
	 */
	void setLevel (double dBlevel) {
		pulseOx.level = pow(10,(dBlevel-12)/20);
		osc->setAmplitude(pow(10,((float)dBlevel-12)/20));

		for (int i=0; i <audioChain.size(); i++)  // update with all audio params
			audioChain[i]->setMasterLevel(pulseOx.level);
	}


	/** Updates pulseOx.period from new heart rate information.  Called from GUIcomponent
	 */
	void setRate (double bpm) {
		HR = roundDoubleToInt(bpm);
		pulseOx.period = roundDoubleToInt(1000*60/bpm);	// take in heart rate in bpm and convert to duration in ms
		for (int i=0; i <audioChain.size(); i++)
			audioChain[i]->setHeartRate(pulseOx.period);
	}


	/** Sets the pulse-ox frequency and updates pulseOx.freqRad.  Then sends info to audioChain elements
	 *  primarily for sheppard scale and harmonic offset.
	 */
	void setFrequency (double sat_) {
		SAT = jlimit(1, 100, roundDoubleToInt(sat_));
		double freq = PULSE_OX_FREQ-5*(100-SAT);
        double cyclesPerSample = freq / sampleRate;
        pulseOx.freqRad = cyclesPerSample * 2.0 * double_Pi;
		osc->setFrequency(freq);

		for (int i=0; i <audioChain.size(); i++)
			audioChain[i]->setMasterFrequency(freq);
	}
	

	/** Processes audio block by passing to each element of the audioChain's processBuffer() function.
	 */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
    {

		bufferToFill.clearActiveBufferRegion();
		
		if (0){//!getCAD()) { // if not processing pulse-ox CAD

			AudioSourceChannelInfo tempBufferInfo;	
			AudioSampleBuffer tempBuffer (1, bufferToFill.numSamples);
			tempBufferInfo.buffer=&tempBuffer;	
			tempBufferInfo.startSample=bufferToFill.startSample;
			tempBufferInfo.numSamples = bufferToFill.numSamples;

			osc->getNextAudioBlock(tempBufferInfo);	// put CAD info in a temp buffer

			for (int i=0; i<audioChain.size(); i++) {	// apply pulse width to temp buffer
				if (audioChain[i]->getType() == GATE)
					audioChain[i]->processBuffer(tempBufferInfo, &state);
			}

			
			for (int i=0; i<audioChain.size(); i++) // apply Fx to sound files
				audioChain[i]->processBuffer(bufferToFill, &state);

			bufferToFill.buffer->addFrom(0, 0, tempBuffer, 0, 0, bufferToFill.numSamples); // sum buffers

		}
		else {
			for (int i=0; i<audioChain.size(); i++) {
				if (audioChain[i]->getType() == FM)

					osc->setFrequency((PULSE_OX_FREQ-5*(100-SAT)) + audioChain[i]->getFMphase(bufferToFill));
			}

			bufferToFill.clearActiveBufferRegion();

			osc->getNextAudioBlock(bufferToFill);

			for (int i=0; i<audioChain.size(); i++) 
				audioChain[i]->processBuffer(bufferToFill, &state);
		}

	}
	

	~SineAudioSource() {	
		mxDestroyArray(state); state=NULL;

		foolibTerminate();
		mclTerminateApplication();

		osc->~ToneGeneratorAudioSource();
		stopThread(2000);
	}
private:
	// related to sinusoidal generation
    double sampleRate, SAT, HR;
	OwnedArray<AcousticFilter> audioChain;
	unsigned int timeNow;
	ToneGeneratorAudioSource *osc;
	bool cad;

protected:
	mxArray *state;
};
