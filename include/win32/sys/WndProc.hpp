/**
 * @file WindowProc.hpp
 *
 */

#ifndef WINDOW_PROC_HPP_
#define WINDOW_PROC_HPP_

#include <windows.h>


namespace sys {

/**
 * Runs event handlers for any messages in the calling thread's message queue.
 * @param window A handle to the window whose messages are to be retrieved. The
 *   window must belong to the current thread. If NULL, messages of all windows
 *   in this thread are processed.
 * @return true if WM_QUIT was not encountered while processing messages
 */
bool handleEvents(HWND window = NULL);

/** 
 * @see "WindowProc callback function" in MSDN
 */
LRESULT CALLBACK handler(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

}	// namespace sys

#endif /* WINDOW_PROC_HPP_ */
