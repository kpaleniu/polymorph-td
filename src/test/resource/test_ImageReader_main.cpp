
#include "resource/ImageReader.hpp"
#include "gr/TestWindow.hpp"

#include <gr/opengl.hpp>

#include <text/util.hpp>

#include <Debug.hpp>

// print tag
namespace {
const char* TAG = "ImageReaderTest";
}

/**
 * Windows main.
 */
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE, LPSTR, int)
{
	using namespace gr;
	using namespace resource;

	DEBUG_OUT(::TAG, "Starting test");

	createTestWindow(hInstance);

	GLuint texId = 0;

	try
	{
		// Yea, change this before running the test...
		static text::string_hash urlHash = text::intern( R"(C:\Programmering\PolyMorphTD\data\images\test.png)" );

		auto surface = createSurface();

		ImageReader imReader;
		auto imageHandle = imReader.getImage(urlHash);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);

		glEnable(GL_TEXTURE_2D);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageHandle->getWidth(),
					imageHandle->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
					imageHandle->data());

		glBindTexture(GL_TEXTURE_2D, texId);

		while (updateTestWindow())
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 0.0);
			glTexCoord2f(1.0, 0.0); glVertex3f( 0.5, -0.5, 0.0);
			glTexCoord2f(1.0, 1.0); glVertex3f( 0.5,  0.5, 0.0);
			glTexCoord2f(0.0, 1.0); glVertex3f(-0.5,  0.5, 0.0);
			glEnd();

			surface.flipBuffers();
		}


	}
	catch (std::exception& e)
	{
		DEBUG_OUT(::TAG, e.what());
	}
	catch (...)
	{
		DEBUG_OUT(::TAG, "Error");
	}

	if (texId != 0)
		glDeleteTextures(1, &texId);

	destroyTestWindow();

	DEBUG_OUT(::TAG, "Closing");

	return 0;
}
