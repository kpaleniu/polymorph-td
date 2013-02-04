
#include <sys/UISystem.hpp>
#include <sys/GraphicsSystem.hpp>

#include <gr/RenderPass.hpp>
#include <gr/opengl.hpp>
#include <gr/Texture.hpp>
#include <gr/Sprite.hpp>
#include <gr/SpriteSheet.hpp>

#include <text/util.hpp>

#include <Debug.hpp>

// print tag
namespace {

const char* TAG = "GUITest";

}

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR, int)
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

		uiSystem.join();
	}
	catch (std::exception& e)
	{
		DEBUG_OUT(TAG, e.what());
	}
	catch (...)
	{
		DEBUG_OUT(TAG, "Error");
	}


	return 0;
}
