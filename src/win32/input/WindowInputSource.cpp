/**
 * @file WindowInputSource.cpp
 *
 */

#include "input/WindowInputSource.hpp"

#include <sys/WindowException.hpp>

#include <Debug.hpp>
#include <Assert.hpp>
#include <Cpp11.hpp>

#include <array>

namespace input {

namespace {

const char* TAG = "WindowInputSource";

#ifndef NO_CONSTEXPR

constexpr std::array<USHORT, 3> downButtons =
{{
	RI_MOUSE_LEFT_BUTTON_DOWN,
	RI_MOUSE_RIGHT_BUTTON_DOWN,
	RI_MOUSE_MIDDLE_BUTTON_DOWN
}};
constexpr std::array<USHORT, 3> upButtons =
{{
	RI_MOUSE_LEFT_BUTTON_UP,
	RI_MOUSE_RIGHT_BUTTON_UP,
	RI_MOUSE_MIDDLE_BUTTON_UP
}};

constexpr pointer_id mouseID = 1;
constexpr size_t buttonCount = downButtons.size();

#else

const std::array<USHORT, 3> downButtons =
{{
	RI_MOUSE_LEFT_BUTTON_DOWN,
	RI_MOUSE_RIGHT_BUTTON_DOWN,
	RI_MOUSE_MIDDLE_BUTTON_DOWN
}};
const std::array<USHORT, 3> upButtons =
{{
	RI_MOUSE_LEFT_BUTTON_UP,
	RI_MOUSE_RIGHT_BUTTON_UP,
	RI_MOUSE_MIDDLE_BUTTON_UP
}};

#define buttonCount 3
#define mouseID pointer_id(1);

#endif

// NOTE: return type and user data index macro of GetWindowLongPtr()
// are dependent on target architecture (64-bit or 32-bit).
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

}	// anonymous namespace

LRESULT CALLBACK handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE:
	{
		// DEBUG_OUT(TAG, "WM_CREATE");

		// set pointer to Window as the HWND user data
		// NOTE: receives last argument of CreateWindowEx() as lpCreateParams
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		setUserData(hwnd, pCreate->lpCreateParams);
		return 0;
	}

	case WM_ACTIVATE:
	{
		// DEBUG_OUT(TAG, "WM_ACTIVATE");

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
		// DEBUG_OUT(TAG, "WM_CLOSE");

		// TODO: show confirmation dialog?
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
	{
		// DEBUG_OUT(TAG, "WM_SIZE");

		//Window* thiz = getUserData<Window*>(hwnd);
		//int width  = LOWORD(lParam);
		//int height = HIWORD(lParam);
		// thiz->_winEventQueue.push(WindowEvent(RESIZE, width, height));
		return 0;
	}

	case WM_CHAR:
	{
		// DEBUG_OUT(TAG, "WM_CHAR");

		WindowInputSource* thiz = getUserData<WindowInputSource*>(hwnd);
		thiz->keyboardInput(msg, wParam, lParam);
		return 0;
	}
	case WM_INPUT:
	{
		WindowInputSource* thiz = getUserData<WindowInputSource*>(hwnd);
		thiz->handleRawInput(wParam, lParam);
		return 0;
	}
	default:
		// DEBUG_OUT(TAG, "Unhandled message.");
		break;
	}

	// allow the default event handler to process the message
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


WindowInputSource::WindowInputSource(HWND window)
:	_window(window),
 	_mouseState({0})
{
	// get raw input data from the mouse/pointer device
	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage     = 0x02;
	rid.dwFlags     = RIDEV_INPUTSINK;
	rid.hwndTarget  = _window;
	VERIFY(RegisterRawInputDevices(&rid, 1, sizeof(rid)));
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
	bool buttonDownEvents[buttonCount] = {false, false, false};
	bool buttonUpEvents[buttonCount] = {false, false, false};

	// Update _mouseState

	for (size_t i = 0; i < downButtons.size(); ++i)
	{
		if ( (mouse.usButtonFlags & downButtons[i]) != 0)
		{
			buttonDownEvents[i] = true;
			_mouseState.buttonDownFlags |= downButtons[i];
		}
	}
	for (size_t i = 0; i < upButtons.size(); ++i)
	{
		if ( (mouse.usButtonFlags & upButtons[i]) != 0)
		{
			buttonUpEvents[i] = true;
			_mouseState.buttonDownFlags &= ~downButtons[i];
		}
	}

	//

	// Notify button up / down events

	POINT cursorPoint;
	if ( !GetCursorPos(&cursorPoint) )
		throw sys::WindowException("Unable to get cursor position.");

	if ( !ScreenToClient(_window, &cursorPoint))
		throw sys::WindowException("Unable to map cursor to window.");

	for (size_t i = 0; i < downButtons.size(); ++i)
	{
		if (buttonDownEvents[i])
		{
			notifyPointerDown(mouseID, pointer_button(i), cursorPoint.x, cursorPoint.y);
		}
		else if (buttonUpEvents[i])
		{
			notifyPointerUp(mouseID, pointer_button(i), cursorPoint.x, cursorPoint.y);
		}
	}

	//

	// Notify pointer move / drag

	int dx = int(mouse.lLastX);
	int dy = int(mouse.lLastY);

	if (dx != 0 && dy != 0)
	{
		bool dragging = (_mouseState.buttonDownFlags & downButtons[0]) != 0;

		if (dragging)
			notifyPointerDrag(mouseID, dx, dy);
		else
			notifyPointerMove(mouseID, dx, dy);
	}

	//

	// Notify wheel (zoom)
	if ( (mouse.usButtonFlags & RI_MOUSE_WHEEL) != 0 )
		notifyPointerZoom( short(mouse.usButtonData) / WHEEL_DELTA );
	//
}

void WindowInputSource::keyboardInput(UINT unsignedInt,
                                      WPARAM unsignedInt1,
                                      LPARAM longInt)
{
    // TODO Implement
}

void WindowInputSource::handleRawInput(WPARAM wParam, LPARAM lParam)
{
	// Only process input when the application is on the foreground.
	if (wParam != RIM_INPUT)
		return;

	RAWINPUT input;
	UINT szData = sizeof(input), szHeader = sizeof(RAWINPUTHEADER);
	HRAWINPUT handle = reinterpret_cast<HRAWINPUT>(lParam);

	if (GetRawInputData(handle, RID_INPUT, &input, &szData, szHeader) != szData)
		throw sys::WindowException("Unable to get raw input data.");

	switch (input.header.dwType)
	{
		case RIM_TYPEMOUSE:
			mouseInput(input.data.mouse);
			break;
	}
}

}	// namespace input
