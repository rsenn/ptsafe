#include "GUIcomponent.h"

/** XmlDocumentFile
 *  This class handles both saving and loading of GUI settings to an XML-style file.  Each element of the
 *  audioChain is passed in, and is parsed in put into XML format.  Once all elements have been read-in, 
 *  the file is saved to disk.  For loading, the reverse procedure is used.  The GUIComponent is 
 *  responsible for passing in all of the elements of the audioChain on save, and for handling all of the
 *  attributes on loading.
 */
class XmlDocumentFile: public FileBasedDocument
{
public:
	XmlDocumentFile():
		FileBasedDocument(String(".xml"),
						 String("*.xml"),
						 String("Choose Settings to load"),
						 String("Save settings"))
	{
		settingsList = new XmlElement("VITALS");
	}

	~XmlDocumentFile() {
	}

	void changed(void) {

	}

/** saveXML(int order, AudioParameter *audioParam)
 *  Adds information for an audio parameter to the save-list.  The order specifies its place
 *  in the chain, and audioParam is a reference to the AudioParameter at that order.  This function
 *  compiles all of the information into an XML file for storage.
 */
	void saveXML(int order, AudioParameter *audioParam){
		
		if (order==0)
			settingsList->deleteAllChildElements();

		// create an inner element
		XmlElement* component = new XmlElement("COMPONENT");

		component->setAttribute("order", audioParam->getOrder());
		component->setAttribute("vitalID", audioParam->getVitalID());
		component->setAttribute("urgency", (double)audioParam->getUrgency());
		component->setAttribute("alarmID", audioParam->getAlarmID());

		VitalSignParams params = audioParam->getVitalSignParams(audioParam->getVitalID());
		
		component->setAttribute("vitalVal", params.val);
		component->setAttribute("upperThMax", params.uppth_dang);
		component->setAttribute("upperThMin", params.uppth_warn);
		component->setAttribute("lowerThMax", params.lowth_warn);
		component->setAttribute("lowerThMin", params.lowth_dang);
		component->setAttribute("absMin", params.absmin);
		component->setAttribute("absMax", params.absmax);
		component->setAttribute("skew", params.skew);
		component->setAttribute("lowerUrgDang", params.lowurg_dang);
		component->setAttribute("lowerUrgWarn", params.lowurg_warn);
		component->setAttribute("upperUrgWarn", params.uppurg_warn);
		component->setAttribute("upperUrgDang", params.uppurg_dang);
		component->setAttribute("normalUrg", params.normurg);
		
		if (audioParam->getAlarmID() == AUDIOFILE) {
			component->setAttribute("soundFile0", audioParam->getSoundFile0());
			component->setAttribute("soundFile1", audioParam->getSoundFile1());
		}
		
		// .. and add our new element to the parent node
		settingsList->addChildElement(component);
	}

/** This returns an XML element of the selected file.
 */
	XmlElement loadXML(void) {
		loadFromUserSpecifiedFile(true);
		return *settingsList;
	}

/** Loads the last XML Element.
 */
	XmlElement loadLastXmlElement(void) {
		return *settingsList;
	}


protected:
    const String getDocumentTitle() {
		return String("PT-SAFE Settings");
	}

/** Handles the user-selected file.
 */
    const String loadDocument (const File& file) {
		XmlDocument doc (file);
		if(settingsList->getNumChildElements() > 0)	// see if there are remaining children from previous loads
			settingsList->deleteAllChildElements();

		settingsList = doc.getDocumentElement();		// convert from xmldoc to xmlelem

		if (settingsList == 0 || !settingsList->hasTagName("VITALS"))
			return String("Not a valid GUI Settings file");		// make sure it is OUR xml file

		setLastDocumentOpened(file);	// this may be handled internally by load()
		return String::empty;
	}

/** Writes save-file to disk.
 */
    const String saveDocument (const File& file) {
		File saveFile = file;

		if(settingsList->writeToFile(saveFile, String::empty)) {		// if it properly writes to disk
			settingsList->deleteAllChildElements();
			return String::empty;
		}
		else
			return String("Did not write to disk, d'oh!");
	}

    const File getLastDocumentOpened() {
		return lastDoc;
	}

    void setLastDocumentOpened (const File& file) {
		lastDoc = file;
	}

private:
	ScopedPointer<XmlElement> settingsList;
	File lastDoc;
};