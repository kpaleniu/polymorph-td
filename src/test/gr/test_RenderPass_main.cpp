
#include "gr/TestWindow.hpp"
#include "gr/opengl.hpp"

#include <Debug.hpp>

// print tag
namespace {
const char* TAG = "RenderPassTestMain";
}

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR, int)
{
	DEBUG_OUT(TAG, "Starting test");

	createTestWindow(hInstance);

	try
	{
		auto surface = createSurface();
		surface.activate();

		while (updateTestWindow())
		{
			glClear(GL_COLOR_BUFFER_BIT);
			surface.flipBuffers();
		}
	}
	catch (...)
	{
		DEBUG_OUT(TAG, "Error");
	}

	destroyTestWindow();

	DEBUG_OUT(TAG, "Closing");

	return 0;
}
