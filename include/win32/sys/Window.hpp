/**
 * @file Window.hpp
 *
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "gr/Surface.hpp"
#include <memory>
#include <windows.h>


namespace sys {
namespace detail {

/**
 * Custom deleter type to for HWND__ pointers.
 */
struct window_deleter {
	void operator()(HWND window);
};

}


class Window : NonCopyable
{
public:
	struct Rect
	{
		int left;
		int top;
		int w;
		int h;
	};

	struct ConstructionData
	{
		HINSTANCE hInstance;
		Rect winRect;
	};

public:

	/**
	 * 
	 */
	Window(const ConstructionData& desc);

	/**
	 * TODO: detach from sys::Window ?
	 */
	gr::Surface& surface();

	/**
	 * Handles all pending window events.
	 * @return true if WM_QUIT was not encountered while processing messages
	 */
	bool handleEvents();

	/**
	 * Shows or hides the window.
	 * @return true if the window was visible previously
	 */
	bool show(bool show = true);

	/**
	 * @return A handle to the underlying native window
	 */
	HWND nativeHandle();

private:	// NOTE: surface has to be destroyed before the window

	std::unique_ptr<HWND__, detail::window_deleter> _windowHandle;
	gr::Surface _surface;
};

}

#endif /* WINDOW_HPP_ */
