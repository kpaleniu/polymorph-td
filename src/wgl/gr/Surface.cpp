/**
 * @file Surface_WGL.cpp
 *
 * Windows GL implementation of surface.
 */

#include "gr/Surface.hpp"

#include "gr/SurfaceException.hpp"

#include <Assert.hpp>
#include <Debug.hpp>

#include <windows.h>
#include <gl/gl.h>

namespace gr {
namespace { const char* TAG = "Surface"; }
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
	DEBUG_OUT(TAG, "Destroying rendering context");

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
	// instead of a TCHAR buffer and easily convert to std::string.
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


Surface::Surface(HWND win)
	: _win(win),
	  _deviceHandle(GetDC(win), detail::dc_deleter(win)),
	  _glHandle()
{
	if (!_deviceHandle)
	{
		ERROR_OUT(TAG, "Device handle cannot be created. HWND=%1%", long(win));
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

		ERROR_OUT(TAG, "Surface::activate error %1%", err);

		msg += detail::getWin32Message(err);
		throw SurfaceException(msg);
	}
}

void Surface::flipBuffers()
{
	glFinish();
	VERIFY(SwapBuffers(_deviceHandle.get()));
}

Rect<long> Surface::getScreenRect() const
{
	// TODO Check if this is thread safe, maybe getting from OpenGL's viewport is better.
	RECT rect;
	GetClientRect(_win, &rect);

	return Rect<long>(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
}

ClipVector Surface::pick(const SurfaceVector& surfVec,
                         real_t depth) const
{
	RECT rect;
	GetClientRect(_win, &rect);
	
	Vector3_r clipV
	{
		2.0f 
		 * (static_cast<const Vector2_r&>(surfVec)(0,0) - real_t(rect.left))
		 / real_t(rect.right - rect.left) - 1.0f,
		2.0f
		 * (static_cast<const Vector2_r&>(surfVec)(1,0) - real_t(rect.bottom))
		 / real_t(rect.top - rect.bottom) - 1.0f,
		2.0f * depth - 1.0f
	};

	return ClipVector(clipV);
}

SurfaceVector Surface::unPick(const ClipVector& clipVec) const
{
	RECT rect;
	GetClientRect(_win, &rect);
	
	Vector2_r surfV
	{
		0.5f 
		 * real_t(rect.right - rect.left)
		 * (static_cast<const Vector3_r&>(clipVec)(0,0) + 1) 
		 + real_t(rect.left),
		0.5f 
		 * real_t(rect.top - rect.bottom)
		 * (static_cast<const Vector3_r&>(clipVec)(1,0) + 1) 
		 + real_t(rect.bottom)
	};

	return SurfaceVector(surfV);
}

}

