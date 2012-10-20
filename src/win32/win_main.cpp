/**
 * @file win_main.cpp
 *
 * Holds the definition of the main function for Windows OS.
 */

#include <sys/GraphicsSystem.hpp>
#include <sys/UISystem.hpp>

#include <Debug.hpp>

#include <input/InputSource.hpp>

// print tag
namespace { const char* TAG = "Main"; }

class TestSurfaceListener : public input::SurfaceListener
{
public:
	TestSurfaceListener()
			: quitRequested(false)
	{
	}

	virtual void onResize(int w, int h)
	{

	}
	virtual void onShow()
	{

	}
	virtual void onHide()
	{

	}
	virtual void onQuit()
	{
		quitRequested = true;
	}

	bool quitRequested;
};

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE,
                     LPSTR /*lpCmdLine*/,
                     int /*nShowCmd*/)
{
	DEBUG_OUT(TAG, "Hello World!");

	sys::Window::ConstructionData winData = { hInstance,
	                                          { 64,
	                                            64,
	                                            800,
	                                            600 } };

	sys::UISystem uiSystem(winData, sys::TimeDuration::millis(60));
	uiSystem.start();

	uiSystem.actionQueue().pushAction([](sys::UISystemRunner& uiRunner){ DEBUG_OUT("ACTION", "TEST"); });


	concurrency::Thread::sleep(sys::TimeDuration::millis(500));

	uiSystem.interrupt();

	uiSystem.join();
	DEBUG_OUT(TAG, "UI system is shut down");

	profiler::ThreadProfiler::dumpAll(std::cout);
	profiler::ThreadProfiler::shutdown();
	text::clearInterned();


	return 0;
}
