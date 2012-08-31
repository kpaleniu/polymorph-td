/**
 * @file Surface_WGL.cpp
 *
 * Windows GL implementation of surface.
 */

#include "gr/Surface.hpp"
#include "sys/Window.hpp"

#include <windows.h>
#include <wingdi.h>

#include <gl/gl.h>

namespace gr {

Surface::Surface(sys::Window &win)
		: _win(win)
{
	HWND hwnd = win.getWindowHandle();

	HDC hdc = GetDC(hwnd);

	//if (!_deviceHandle)
	//		throw WindowException("Unable to create device context");

	// set the pixel format we want
	PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), // size of structure
	                              1, // default version
	                              PFD_DRAW_TO_WINDOW
	                              | // window drawing support
	                              PFD_SUPPORT_OPENGL
	                              | // OpenGL support
	                              PFD_DOUBLEBUFFER, // double buffering support
	                              PFD_TYPE_RGBA, // RGBA color mode
	                              32, // 32 bit color mode
	                              0,
	                              0,
	                              0,
	                              0,
	                              0,
	                              0, // ignore color bits, non-palettized mode
	                              0, // no alpha buffer
	                              0, // ignore shift bit
	                              0, // no accumulation buffer
	                              0,
	                              0,
	                              0,
	                              0, // ignore accumulation bits
	                              16, // 16 bit z-buffer size
	                              8, // no stencil buffer
	                              0, // no auxiliary buffer
	                              PFD_MAIN_PLANE, // main drawing plane
	                              0, // reserved
	                              0,
	                              0,
	                              0 }; // layer masks ignored

	GLuint pixelFormat;

	// FIXME Throwing exception doesn't destroy window.

	// choose best matching pixel format
	if (!(pixelFormat = ChoosePixelFormat(hdc,
	                                      &pfd)))
	{
		// throw WindowException("Can't find an appropriate pixel format");
	}

	// set pixel format to device context
	if (!SetPixelFormat(hdc,
	                    pixelFormat,
	                    &pfd))
	{
		// throw WindowException("Unable to set pixel format");
	}

	// create the OpenGL rendering context
	if (!(_glHandle = wglCreateContext(hdc)))
	{
		// throw WindowException("Unable to create OpenGL rendering context");
	}

	// now make the rendering context the active one
	if (!wglMakeCurrent(hdc, _glHandle))
	{
		// throw WindowException("Unable to activate OpenGL rendering context");
	}
}

Surface::~Surface()
{

}

void Surface::flipBuffers()
{
	// SwapBuffers(_deviceHandle);
}

}
