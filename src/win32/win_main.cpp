/**
 * @file win_main.cpp
 * 
 * Holds the definition of the main function for Windows OS.
 */

#include <action/WorldAction.hpp>
#include <gr/Renderer.hpp>
#include <sys/Window.hpp>
#include <sys/WorldSystem.hpp>

#include <Debug.hpp>

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE,
                     LPSTR /*lpCmdLine*/,
                     int /*nShowCmd*/)
{
	DEBUG_OUT("Hello World!");

	sys::Window::ConstructionData winData = { hInstance, { 64, 64, 800, 600 } };
	sys::Window window(winData);
	window.show();

	gr::Renderer renderer(window.surface());
	sys::WorldSystem worldSystem(renderer, sys::TimeDuration::millis(33));

	worldSystem.start();
	worldSystem.waitForStartup();
	
	DEBUG_OUT("Writing actions");
	
	int index = 0, errs = 0;
	while (window.handleEvents())
	{
		try
		{
			action::world_action::TestAction::Data data = { index, index + 1 };
			worldSystem.actionQueue().writeAction(action::world_action::TestAction,
			                                      data);
			++index;
		}
		catch (stream::StreamException &e)
		{
			DEBUG_OUT(e.what());
			concurrency::Thread::sleep(sys::TimeDuration::millis(10));
			++errs;
		}
	}

	DEBUG_OUT("Exceptions: " << errs);
	return 0;
}
