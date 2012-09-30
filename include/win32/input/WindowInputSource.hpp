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
 * Runs event handlers for any messages in the calling thread's message queue.
 *
 * @param window 	A handle to the window whose messages are to be retrieved.
 * 					The window must belong to the current thread. If NULL,
 * 					messages of all windows in this thread are processed.
 * @return 			true if WM_QUIT was not encountered while processing messages
 */
bool handleEvents(HWND window = NULL);

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
	// Only called by handler:

	void mouseInput(const RAWMOUSE& mouse);
	void keyboardInput(UINT, WPARAM /*wParam*/, LPARAM);

private:
	HWND _window;
};

}	// namespace sys

#endif /* WINDOW_PROC_HPP_ */
