/**
 * @file Surface_WGL.cpp
 *
 * Windows GL implementation of surface.
 */

#include "gr/Surface.hpp"
#include "gr/SurfaceException.hpp"
#include "sys/Window.hpp"
#include "Assert.hpp"

#include <windows.h>
#include <gl/gl.h>


namespace gr {
namespace detail {

dc_deleter::dc_deleter(HWND window)
	: _window(window)
{
}

void dc_deleter::operator()(HDC dc)
{
	VERIFY(ReleaseDC(_window, dc));
}

void rc_deleter::operator()(HGLRC rc)
{
	// NOTE: if the rendering context is active in some other thread,
	// wglDeleteContext() will produce an error
	VERIFY(wglDeleteContext(rc));
}

}	// namespace detail


Surface::Surface(sys::Window &win)
	: _win(win),
	  _deviceHandle(GetDC(win.nativeHandle()), detail::dc_deleter(win.nativeHandle())),
	  _glHandle()
{
	if (!_deviceHandle)
		throw SurfaceException("Unable to get device context");

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));

	pfd.nSize        = sizeof(pfd);
	pfd.nVersion     = 1; // default version
	pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType   = PFD_TYPE_RGBA;
	pfd.cColorBits   = 32;
	pfd.cDepthBits   = 16;
	pfd.cStencilBits = 8;
	pfd.iLayerType   = PFD_MAIN_PLANE; // main drawing plane

	// choose best matching pixel format
	int pixelFormat = ChoosePixelFormat(_deviceHandle.get(), &pfd);
	if (pixelFormat == 0 || !SetPixelFormat(_deviceHandle.get(), pixelFormat, &pfd))
	{
		throw SurfaceException("Unable to set pixel format for context");
	}

	// create the OpenGL rendering context
	_glHandle.reset(wglCreateContext(_deviceHandle.get()));
	if (!_glHandle)
	{
		throw SurfaceException("Unable to create OpenGL rendering context");
	}

	activate(true);
}

Surface::~Surface()
{
}

bool Surface::isActive() const
{
	return (wglGetCurrentContext() == _glHandle.get());
}

void Surface::activate(bool activate)
{
	BOOL success = activate ?
		wglMakeCurrent(_deviceHandle.get(), _glHandle.get()) :
		wglMakeCurrent(0, 0);

	if (!success)
		throw SurfaceException("Unable to activate OpenGL rendering context");
}

void Surface::flipBuffers()
{
	VERIFY(SwapBuffers(_deviceHandle.get()));
}

}
