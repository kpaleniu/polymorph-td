/**
 * @file win_main.cpp
 * 
 * Holds the definition of the main function for Windows OS.
 */

#include <sys/WorldSystem.hpp>

#include <action/WorldAction.hpp>

#include <iostream>
using namespace std;

#include <Debug.hpp>

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
	                                          { 0,
	                                            0,
	                                            800,
	                                            600 } };

	sys::WorldSystem worldSystem(sys::TimeDuration::millis(33),
	                             winData);

	worldSystem.start();

	worldSystem.waitForStartup();

	concurrency::Thread::sleep(sys::TimeDuration::millis(2500));

	DEBUG_OUT("Writing actions");

	int errs = 0;

	for (int i = 0; i < 500; ++i)
	{
		try
		{
			action::world_action::TestAction::Data data = { i,
			                                                i
			                                                + 1 };
			worldSystem.actionQueue().writeAction(action::world_action::TestAction,
			                                      data);
		}
		catch (stream::StreamException &e)
		{
			cout << e.what() << endl;
			concurrency::Thread::sleep(sys::TimeDuration::millis(10));
			++errs;
		}

	}

	cout << "Exceptions: " << errs << endl;
	return 0;
}
