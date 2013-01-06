/**
 * @file WindowProc.hpp
 *
 */

#ifndef WINDOW_PROC_HPP_
#define WINDOW_PROC_HPP_

#include "input/InputSource.hpp"
#include <windows.h>

namespace input {

/** 
 * @see "WindowProc callback function" in MSDN
 */
LRESULT CALLBACK handler(HWND window,
                         UINT msg,
                         WPARAM wParam,
                         LPARAM lParam);

class WindowInputSource : public InputSource
{
public:
	// Source of events.
	friend LRESULT CALLBACK handler(HWND window,
	                                UINT msg,
	                                WPARAM wParam,
	                                LPARAM lParam);

	/**
	 * Constructor.
	 * @param window	The window handle that's used as low-level source of
	 * 					input. This handle must have a window as user data
	 * 					that returns a reference to this instance when
	 * 					calling method Window::inputSource().
	 *
	 * 					Note: The user data could be replaced to hold a
	 * 					pointer to this instance.
	 */
	WindowInputSource(HWND window);
	bool handleInput();

private:
	struct MouseState
	{
		USHORT buttonDownFlags;
	};

private:
	void handleRawInput(WPARAM wParam, LPARAM lParam); // Only called by handler

	void mouseInput(const RAWMOUSE& mouse);
	void keyboardInput(UINT, WPARAM /*wParam*/, LPARAM);

private:
	HWND _window;
	MouseState _mouseState; // State of mouse buttons.
};

}	// namespace sys

#endif /* WINDOW_PROC_HPP_ */
