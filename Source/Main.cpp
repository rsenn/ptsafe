
#include "../JuceLibraryCode/JuceHeader.h"
#include "MainAppWindow.h"


//==============================================================================
class SoundGUIApplication  : public JUCEApplication
{
public:
    //==============================================================================
    SoundGUIApplication()   : mainWindow (0)
    {
        // Don't do anything in this constructor! It will be called before the
        // main Juce subsystem has been initialised!
    }

    ~SoundGUIApplication()
    {
        // Don't do anything in this destructor! It will be called after the
        // main Juce subsystem has been shutdown and is no longer valid!
    }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        // Do your application's initialisation code here..
        mainWindow = new MainAppWindow();
    }

    void shutdown()
    {
        // Do your application's shutdown code here..
        deleteAndZero (mainWindow);
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        quit();
    }

    //==============================================================================
    const String getApplicationName()
    {
        return "Sound GUI";
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        
    }

private:
    MainAppWindow* mainWindow;
};

//==============================================================================
// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(SoundGUIApplication)
