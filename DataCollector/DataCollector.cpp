// DataCollector.cpp : Defines the entry point for the console application.
//
#include "DataCollectorListener.h"
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// Create a sample listener and controller
	DataCollectorListener listener;
	Controller controller;

	// Have the sample listener receive events from the controller
	controller.addListener(listener);

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	// Remove the sample listener when done
	controller.removeListener(listener);
	return 0;
}


