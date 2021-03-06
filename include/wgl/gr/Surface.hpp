#pragma once

#include "gr/types.hpp"

#include <NonCopyable.hpp>
#include <Rect.hpp>

#include <memory>
#include <windows.h>
#include <wingdi.h>


namespace sys {
class Window;
}

namespace polymorph { namespace gr {
namespace detail {

/**
 * Custom deleter type to for HDC__ pointers.
 */
class dc_deleter
{
public:
	explicit dc_deleter(HWND window);
	void operator()(HDC dc);

private:
	HWND _window;
};

/**
 * Custom deleter type to allow HGLRC__ pointers.
 */
struct rc_deleter
{
    void operator()(HGLRC rc);
};

}


/**
 *
 * TODO: Append GetLastError() information to thrown exceptions.
 */
class Surface : NonCopyable
{
public:
	Surface(HWND win);
	Surface(Surface&& surface);

	~Surface();

	/**
	 * @return true if the underlying rendering context is active in the calling thread.
	 */
	bool isActive() const;

	/**
	 * Activate/deactivate the underlying rendering context for the calling thread.
	 */
	void setActive(bool activate = true);

	void setVSync(bool enable = true);

	void flipBuffers();

	/**
	 * Gets the drawable area in window coordinates, usually from (0, 0) to window dimension.
	 */
	Rect<long> getScreenRect() const;

	ClipVector pick(const SurfaceVector& surfVec, real_t depth) const;
	SurfaceVector unPick(const ClipVector& clipVec) const;

private:
	HWND _win;
	std::unique_ptr<HDC__,   detail::dc_deleter> _deviceHandle;
	std::unique_ptr<HGLRC__, detail::rc_deleter> _glHandle;

	struct WGLExtensions
	{
		typedef BOOL (GLAPIENTRY * PFNGLSWAPINTERVALPROC) (int interval);

		WGLExtensions();

		bool loaded;

		PFNGLSWAPINTERVALPROC wglSwapInterval;
	} _wglExtensions;
};

} }
