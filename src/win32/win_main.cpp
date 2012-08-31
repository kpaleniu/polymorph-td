/**
 * @file win_main.cpp
 * 
 * Holds the definition of the main function for Windows OS.
 */

#include <sys/WorldSystem.hpp>

#include <iostream>
using namespace std;

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nShowCmd)
{
	cout << "Hello World!" << endl;

	sys::Window::ConstructionData winData = { hInstance,
	                                          hPrevInstance,
	                                          lpCmdLine,
	                                          nShowCmd };

	sys::WorldSystem worldSystem(winData);

	worldSystem.start();

	sys::Thread::sleep(sys::TimeDuration::millis(5000));

	return 0;
}
