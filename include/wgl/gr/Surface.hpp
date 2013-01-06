/**
 * @file Surface.hpp
 *
 */

#ifndef SURFACE_HPP_
#define SURFACE_HPP_

#include <NonCopyable.hpp>
#include <Rect.hpp>

#include <memory>
#include <windows.h>
#include <wingdi.h>


namespace sys {
class Window;
}

namespace gr {
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
	void activate(bool activate = true);

	void flipBuffers();

	/**
	 * Gets the drawable area in window coordinates, usually from (0, 0) to window dimension.
	 */
	Rect<long> getScreenRect() const;

private:
	HWND _win;
	std::unique_ptr<HDC__,   detail::dc_deleter> _deviceHandle;
	std::unique_ptr<HGLRC__, detail::rc_deleter> _glHandle;
};

}

#endif /* SURFACE_HPP_ */
