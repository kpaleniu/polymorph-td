/**
 * @file win_main.cpp
 *
 * Holds the definition of the main function for Windows OS.
 */

#include "game/Game.hpp"

#include "sys/UISystem.hpp"
#include "sys/GraphicsSystem.hpp"

#include "Debug.hpp"

// print tag
namespace {
const char* TAG = "WinMain";
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

		sys::GraphicsSystem& grSystem = uiSystem.waitForGraphicsSystem();

		game::Game theGame(uiSystem, grSystem);

		try
		{ rVal = theGame.enter(); }
		catch (...)
		{}

		uiSystem.interrupt();
		uiSystem.join();
	}
	catch (...)
	{}

	INFO_OUT(TAG, "Systems shut down");

	profiler::ThreadProfiler::dumpAll(std::cout);
	profiler::ThreadProfiler::shutdown();
	text::clearInterned();

	return rVal;
}
