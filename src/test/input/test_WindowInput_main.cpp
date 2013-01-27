
#include "input/InputSource.hpp"

#include <sys/UISystem.hpp>
#include <sys/Window.hpp>
#include <sys/GraphicsSystem.hpp>

#include <gr/types.hpp>

#include <concurrency/Thread.hpp>

#include <Event.hpp>
#include <Debug.hpp>

#include <iostream>

#include <windows.h>

using namespace std;

// print tag
namespace {
const char* TAG = "WindowInputTest";
}

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE,
                     LPSTR /*lpCmdLine*/,
                     int /*nShowCmd*/)
{
	sys::Window::ConstructionData winData = { hInstance,
	                                          { 64,
	                                            64,
	                                            800,
	                                            600 } };

	INFO_OUT(TAG, "Starting systems");

	int rVal = 0;
	try
	{
		sys::UISystem uiSystem(winData);
		uiSystem.start();

		uiSystem.waitForStartup();

		sys::UISystem::StateDesc state;

		state.eventManager.with<sys::event::KeyDown>()
			.actionBindings().push_back([&](const sys::event::KeyDown& event)
			{ DEBUG_OUT(TAG, "onKeyDown(%i)", event.key); });
		state.eventManager.with<sys::event::KeyUp>()
			.actionBindings().push_back([&](const sys::event::KeyUp& event)
			{ DEBUG_OUT(TAG, "onKeyUp(%i)", event.key); });

		state.eventManager.with<sys::event::PointerDown>()
			.actionBindings().push_back([&](const sys::event::PointerDown& event)
			{ DEBUG_OUT(TAG, "onPointerDown(%i, %i, %i, %i)", event.id, event.button, event.x, event.y); });

		uiSystem.pushState(state);

		uiSystem.join();
	}
	catch (...)
	{
		rVal = 1;
	}

	INFO_OUT(TAG, "Systems shut down");

	profiler::ThreadProfiler::dumpAll(std::cout);
	profiler::ThreadProfiler::shutdown();
	text::clearInterned();

	return rVal;
}
