

#ifndef __MAINAPPWINDOW_H_52B5E298__
#define __MAINAPPWINDOW_H_52B5E298__

//[Headers]  
#include "../JuceLibraryCode/JuceHeader.h"
#include "GUIcomponent.h"
//[/Headers]


//==============================================================================
/**
                                                                    //[Comments]
This class is a window that holds GUIcomponent object.
                                                                    //[/Comments]
*/
class MainAppWindow   : public DocumentWindow
{
public:
    //==============================================================================
    MainAppWindow();
    ~MainAppWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void closeButtonPressed();
	//void paint (Graphics& g);
    void resized();

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
	//[UserVariables]   -- You can add your own custom variables in this section.
	Viewport* viewport;
    //[/UserVariables]

    //==============================================================================
	GUIcomponent* component;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MainAppWindow (const MainAppWindow&);
    MainAppWindow& operator= (const MainAppWindow&);
};


#endif  // __MAINAPPWINDOW_H_52B5E298__
