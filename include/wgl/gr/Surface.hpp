/**
 * @file Surface.hpp
 *
 */

#ifndef SURFACE_HPP_
#define SURFACE_HPP_

#include "NonCopyable.hpp"
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
class dc_deleter {
	HWND _window;
public:
	explicit dc_deleter(HWND window);
	void operator()(HDC dc);
};

/**
 * Custom deleter type to allow HGLRC__ pointers.
 */
struct rc_deleter {
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
	Surface(sys::Window &win);
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

private:
	sys::Window &_win;
	std::unique_ptr<HDC__,   detail::dc_deleter> _deviceHandle;
	std::unique_ptr<HGLRC__, detail::rc_deleter> _glHandle;
};

}

#endif /* SURFACE_HPP_ */
