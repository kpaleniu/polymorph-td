/**
 * @file Surface_WGL.cpp
 *
 * Windows GL implementation of surface.
 */

#include "gr/Surface.hpp"
#include "gr/SurfaceException.hpp"
#include "sys/Window.hpp"
#include "Assert.hpp"

#include "Debug.hpp"

#include <windows.h>
#include <gl/gl.h>

// ---------
#include "concurrency/Thread.hpp"

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
	DEBUG_OUT("Destroying context");
	DEBUG_OUT("In thread " << concurrency::Thread::getCurrentID());

	// NOTE: if the rendering context is active in some other thread,
	// wglDeleteContext() will produce an error
	VERIFY(wglDeleteContext(rc));
}

//////////
// COPIED THIS JUST TO SEE THE ERROR DESCRIPTION

// for convenience
struct ScopedLocalFree : NonCopyable {
	ScopedLocalFree(HLOCAL p) : _p(p) {}
	~ScopedLocalFree() { LocalFree(_p); }
private:
	HLOCAL _p;
};

std::string getWin32Message(DWORD error)
{
	LPVOID buffer = NULL;

	// NOTE: force call FormatMessageA so we can use a char buffer
	// instead of a TCHAR buffer and easily convert to text::String
	DWORD ret = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&buffer,
		0,
		NULL);

	if (ret == 0)
		return "Unknown error";

	ScopedLocalFree localfree(buffer);
	return std::string(static_cast<LPCSTR>(buffer));
}

//////////

}	// namespace detail


Surface::Surface(sys::Window &win)
	: _win(win),
	  _deviceHandle(GetDC(win.nativeHandle()), detail::dc_deleter(win.nativeHandle())),
	  _glHandle()
{
	if (!_deviceHandle)
	{
		DEBUG_OUT( "Device handle cannot be created. HWND=" << long(win.nativeHandle()) );
		throw SurfaceException("Unable to get device context");
	}

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
		std::string msg = "Unable to create OpenGL rendering context.\n";
		msg += detail::getWin32Message(GetLastError());
		throw SurfaceException(msg);
	}
}

Surface::Surface(Surface&& surface)
: _win(surface._win),
  _deviceHandle(std::move(surface._deviceHandle)),
  _glHandle(std::move(surface._glHandle))
{
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
	{
		auto err = GetLastError();
		std::string msg = "Unable to activate OpenGL rendering context.\n";

		DEBUG_OUT("Surface::activate error " << err);
		DEBUG_OUT("In thread " << concurrency::Thread::getCurrentID());

		msg += detail::getWin32Message(err);
		throw SurfaceException(msg);
	}
}

void Surface::flipBuffers()
{
	VERIFY(SwapBuffers(_deviceHandle.get()));
}

}
