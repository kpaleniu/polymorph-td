/**
 * @file Window.hpp
 *
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "gr/Surface.hpp"
#include "input/InputSource.hpp"
#include "input/WindowInputSource.hpp"

#include <memory>
#include <windows.h>


namespace sys {
namespace detail {

/**
 * Custom deleter type to for HWND__ pointers.
 */
struct window_deleter
{
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
	 * Shows or hides the window.
	 * @return true if the window was visible previously
	 */
	bool show(bool show = true);

	/**
	 * Access to window input.
	 * @return	Reference to the input source active on this window.
	 */
	input::WindowInputSource& inputSource();

	/**
	 * @return A handle to the underlying native window
	 */
	HWND nativeHandle();

private:	// NOTE: surface has to be destroyed before the window

	std::unique_ptr<HWND__, detail::window_deleter> _windowHandle;
	input::WindowInputSource _inputSource;
};

}

#endif /* WINDOW_HPP_ */
