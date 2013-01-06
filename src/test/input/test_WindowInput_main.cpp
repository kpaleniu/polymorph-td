
#include "input/InputSource.hpp"

#include <sys/UISystem.hpp>
#include <sys/GraphicsSystem.hpp>

#include <concurrency/Thread.hpp>

#include <Debug.hpp>

#include <iostream>

#include <windows.h>

using namespace std;

// print tag
namespace {
const char* TAG = "WindowInputTest";
}

class TestSurfaceListener : public input::SurfaceListener
{
public:
	void onResize(int w, int h)	{ DEBUG_OUT(TAG, "onResize(%i, %i)", w, h);	}
	void onShow()				{ DEBUG_OUT(TAG, "onShow()"); }
	void onHide()				{ DEBUG_OUT(TAG, "onHide()"); }
	void onQuit()
	{
		DEBUG_OUT(TAG, "onQuit()");
		concurrency::Thread::interruptCurrent();
	}
} testSurfaceListener;

class TestKeyListener : public input::KeyListener
{
public:
	void onKeyDown(input::key_type key)	{ DEBUG_OUT(TAG, "onKeyDown(%i)", key); }
	void onKeyUp(input::key_type key)	{ DEBUG_OUT(TAG, "onKeyUp(%i)", key); }
} testKeyListener;

class TestPointerListener : public input::PointerListener
{
public:
	void onPointerDown(input::pointer_id id, input::pointer_button button, long x, long y)
	{ DEBUG_OUT(TAG, "onPointerDown(%i, %i, %i, %i)", id, button, x, y); }

	void onPointerMove(input::pointer_id id, int dx, int dy)
	{ DEBUG_OUT(TAG, "onPointerMove(%i, %i, %i)", id, dx, dy); }

	void onPointerDrag(input::pointer_id id, int dx, int dy)
	{ DEBUG_OUT(TAG, "onPointerDrag(%i, %i, %i)", id, dx, dy); }

	void onPointerUp(input::pointer_id id, input::pointer_button button, long x, long y)
	{ DEBUG_OUT(TAG, "onPointerUp(%i, %i, %i, %i)", id, button, x, y); }

	void onPointerZoom(int dz)
	{ DEBUG_OUT(TAG, "onPointerZoom(%i)", dz); }
} testPointerListener;

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

		/*sys::GraphicsSystem& grSystem = */uiSystem.waitForGraphicsSystem();

		auto& window = uiSystem.waitForWindow();

		window.inputSource().setSurfaceListener(&testSurfaceListener);
		window.inputSource().setPointerListener(&testPointerListener);
		window.inputSource().setKeyListener(&testKeyListener);

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
