/**
 * @file WindowInputSource.cpp
 *
 */

#include "input/WindowInputSource.hpp"
#include "sys/WindowException.hpp"

#include "sys/Window.hpp"

namespace sys {
class Window;
}

namespace input {

namespace {

// NOTE: return type and user data index macro of GetWindowLongPtr()
// are dependant on target architecture (64-bit or 32-bit).
#ifdef _WIN64
	#define USERDATA GWLP_USERDATA
	typedef LONG_PTR user_data;
#else
	#define USERDATA GWL_USERDATA
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
	user_data old = SetWindowLongPtr(window, USERDATA, reinterpret_cast<user_data>(ud));
	if (old == 0 && GetLastError())
		throw sys::WindowException("Unable to set window user data");
}

bool handleKeyInput(HWND /*window*/, UINT, WPARAM /*wParam*/, LPARAM)
{
	// Window* thiz = getUserData<Window*>(window);
	// auto key = convertKeyCode(wParam);
	// thiz->_winEventQueue.push(KeyEvent(key));
	// TODO Remove this function and call WindowInputSource::keyboardInput directly.
	return true;
}

bool handleMouseInput(HWND /*window*/, const RAWMOUSE& mouse)
{
	// TODO Remove this function and call WindowInputSource::mouseInput directly.
	return true;
}

bool handleRawInput(HWND window, UINT, WPARAM wParam, LPARAM lParam)
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


// TODO: implement a timeout for the event loop so move/resize events
// don't starve routines running on the same thread
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
	{
		sys::Window* thiz = getUserData<sys::Window*>(hwnd);
		thiz->inputSource().keyboardInput(msg, wParam, lParam);
		return 0;
	}
	case WM_INPUT:
		if (handleRawInput(hwnd, msg, wParam, lParam))
			return 0;
		break;
	default:
		break;
	}

	// allow the default event handler to process the message
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


WindowInputSource::WindowInputSource(HWND window)
: _window(window)
{
}

bool WindowInputSource::handleInput()
{
	MSG msg;
	if (PeekMessage(&msg, _window, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			notifyQuit();
			return true;
		}

		TranslateMessage(&msg); // translate and dispatch to event queue
		DispatchMessage(&msg);

		return true; // More messages might be in queue.
	}

	return false;
}

void WindowInputSource::mouseInput(const RAWMOUSE& mouse)
{
    // TODO Implement

	// mouse button up/down masks
	const USHORT DOWN_MASK = RI_MOUSE_BUTTON_1_DOWN | RI_MOUSE_BUTTON_2_DOWN;
	const USHORT UP_MASK   = RI_MOUSE_BUTTON_1_UP   | RI_MOUSE_BUTTON_2_UP;

	// NOTE: MOUSE_MOVE_RELATIVE == 0x0
	//if (!mouse.usFlags && (mouse.lLastX || mouse.lLastY))
		// TODO: handle relative mouse movement

	if (mouse.usButtonFlags & DOWN_MASK)
	{
		//pointer_button key = convertMouseKey(mouse.usButtonFlags);
		//notifyPointerDown(0, key, int(mouse.lLstX), int(mouse.lLastY))
	}
	else if (mouse.usButtonFlags & UP_MASK)
	{
		//pointer_button key = convertMouseKey(mouse.usButtonFlags);
		//notifyPointerUp(0, key, int(mouse.lLastX), int(mouse.lLastY));
	}
	else if (mouse.usButtonFlags & RI_MOUSE_WHEEL)
	{
		//auto delta = static_cast<SHORT>(mouse.usButtonData);
		//notifyPointerZoom(int(delta));
	}
}

void WindowInputSource::keyboardInput(UINT unsignedInt,
                                      WPARAM unsignedInt1,
                                      LPARAM longInt)
{
    // TODO Implement
}

}	// namespace input
