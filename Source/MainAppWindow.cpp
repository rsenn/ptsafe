
#include "MainAppWindow.h"
#define USE_COMPONENT 1


//==============================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::allButtons),
	  viewport(0)
{

	Component::addAndMakeVisible (viewport = new Viewport ("ViewPort"));
    viewport->setScrollBarsShown (true, false);
    viewport->setScrollBarThickness (12);

#if USE_COMPONENT
	//Component::addAndMakeVisible (component = new GUIcomponent());
	viewport->setViewedComponent(component = new GUIcomponent());
#endif
    centreWithSize (800, 700);
    setVisible (true);
}

MainAppWindow::~MainAppWindow()
{
	deleteAndZero (viewport);
#if USE_COMPONENT
	//deleteAndZero (component);
#endif
}

void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

void MainAppWindow::resized()
{
	viewport->setBounds (0, getTitleBarHeight(), proportionOfWidth (1.0f), getHeight() - getTitleBarHeight());
#if USE_COMPONENT
	//component->setBounds (0, getTitleBarHeight(), proportionOfWidth (1.0f), getHeight() - getTitleBarHeight());
#endif
	
	// note: must call superclass' resized(), otherwise GUI components may not redraw properly
	DocumentWindow::resized();
}