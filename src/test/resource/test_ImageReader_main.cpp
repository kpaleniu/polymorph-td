
#include "resource/ImageReader.hpp"
#include "gr/TestWindow.hpp"

#include <gr/opengl.hpp>
#include <gr/Texture.hpp>

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
		static text::string_hash urlHash = text::intern( R"(.\data\images\test.png)" );

		auto surface = createSurface();

		ImageReader imReader;
		auto imageHandle = imReader.getImage(urlHash);

		glEnable(GL_TEXTURE_2D);

		Texture tex(*imageHandle,
		            Texture::TextureParams
		            { Texture::TextureParams::CLAMP,
					  Texture::TextureParams::CLAMP,
					  Texture::TextureParams::LINEAR,
					  Texture::TextureParams::LINEAR });

		while (updateTestWindow())
		{
			auto bindLock = tex.bindLock();

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
