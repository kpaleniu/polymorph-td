/**
 * @file WndProc.cpp
 *
 * MS Windows implementation of class Window.
 */

#include "sys/WndProc.hpp"
#include "sys/WindowException.hpp"
#include <windows.h>


namespace sys {
class Window;

namespace {

// NOTE: return type of GetWindowLongPtr() macro alias
// is dependant on target architecture (64-bit or 32-bit).
#ifdef _WIN64
    typedef LONG_PTR user_data;
#else
    typedef LONG user_data;
#endif

template <typename T>
T getUserData(HWND window)
{
	user_data ud = GetWindowLongPtr(window, GWLP_USERDATA);
	return reinterpret_cast<T>(ud);
}

template <typename T>
void setUserData(HWND window, T ud)
{
	SetLastError(0);
	user_data old = SetWindowLongPtr(window, GWL_USERDATA, reinterpret_cast<user_data>(ud));
	if (old == 0 && GetLastError())
		throw sys::WindowException("Unable to set window user data");
}

bool handleKeyInput(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Window* thiz = getUserData<Window*>(window);
	// auto key = convertKeyCode(wParam);
	// thiz->_winEventQueue.push(KeyEvent(key));
	return true;
}

bool handleMouseInput(HWND window, const RAWMOUSE& mouse)
{
	// mouse button up/down masks
	const USHORT DOWN_MASK = RI_MOUSE_BUTTON_1_DOWN | RI_MOUSE_BUTTON_2_DOWN;
	const USHORT UP_MASK   = RI_MOUSE_BUTTON_1_UP   | RI_MOUSE_BUTTON_2_UP;

	// NOTE: MOUSE_MOVE_RELATIVE == 0x0
	if (!mouse.usFlags && (mouse.lLastX || mouse.lLastY))
		; // TODO: handle relative mouse movement

	if (mouse.usButtonFlags & DOWN_MASK)
	{
		// TODO: handle mouse button down events
		//auto key = convertMouseKey(mouse.usButtonFlags);
	}
	else if (mouse.usButtonFlags & UP_MASK)
	{
		// TODO: handle mouse button up events
		//auto key = convertMouseKey(mouse.usButtonFlags);
	}
	else if (mouse.usButtonFlags & RI_MOUSE_WHEEL)
	{
		// TODO: handle mouse wheel
		//auto delta = static_cast<SHORT>(mouse.usButtonData);
	}

	return true;
}

bool handleRawInput(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// only process input when the application is on the foreground
	if (wParam != RIM_INPUT)
		return false;

	RAWINPUT input;
	UINT szData = sizeof(input), szHeader = sizeof(RAWINPUTHEADER);
	HRAWINPUT handle = reinterpret_cast<HRAWINPUT>(lParam);

	if (GetRawInputData(handle, RID_INPUT, &input, &szData, szHeader) != szData)
		return false;   // error occurred

	if (input.header.dwType != RIM_TYPEMOUSE)
		return false;   // process only mouse events (for now)

	return handleMouseInput(window, input.data.mouse);
}

}	// anonymous namespace


bool handleEvents(HWND window)
{
	MSG msg;
	while (PeekMessage(&msg, window, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			// _winEventQueue.push(WindowEvent(QUIT_REQUEST, 0, 0));
			// exitCode = msg.wParam;
			return false;
		}

		TranslateMessage(&msg); // translate and dispatch to event queue
		DispatchMessage(&msg);
	}

	return true;
}

LRESULT CALLBACK handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE:
	{
		// set pointer to Window as the HWND user data
		// NOTE: receives last argument of CreateWindowEx() as lpCreateParams
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		setUserData(hwnd, pCreate->lpCreateParams);
		return 0;
	}

	case WM_ACTIVATE:
	{
		//Window* thiz = getUserData<Window*>(hwnd);
		//bool active = LOWORD(wParam) != WA_INACTIVE;
		//bool minimized = HIWORD(wParam);
		//thiz->_winEventQueue.push(WindowEvent(IN/ACTIVATE, 0, 0));

		return 0;
	}

	case WM_SYSCOMMAND: // look for screensavers and powersave mode
		switch (wParam)
		{
			case SC_SCREENSAVE: // screensaver trying to start
			case SC_MONITORPOWER: // monitor going to powersave mode
				// returning 0 prevents either from happening
				return 0;
			default:
				break;
		}
		break;

	case WM_CLOSE:
		// TODO: show confirmation dialog?
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
	{
		//Window* thiz = getUserData<Window*>(hwnd);
		//int width  = LOWORD(lParam);
		//int height = HIWORD(lParam);
		// thiz->_winEventQueue.push(WindowEvent(RESIZE, width, height));
		return 0;
	}

	case WM_CHAR:
		if (handleKeyInput(hwnd, msg, wParam, lParam))
			return 0;

	case WM_INPUT:
		if (handleRawInput(hwnd, msg, wParam, lParam))
			return 0;

	default:
		break;
	}

	// allow the default event handler to process the message
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

}	// namespace sys
