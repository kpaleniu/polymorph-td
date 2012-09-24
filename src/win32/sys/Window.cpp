/**
 * @file Window.cpp
 *
 * MS Windows implementation of class Window.
 */

#include "sys/Window.hpp"

#include "sys/WindowException.hpp"
#include "BuildConfig.hpp"

namespace sys {

Window::Window(ConstructionData &ctorData)
		: _windowHandle(createWindowHandle(ctorData.hInstance, ctorData.winRect)),
		  _surface(*this)
{
	ShowWindow(_windowHandle, SW_SHOW);
	SetForegroundWindow(_windowHandle);
	SetFocus(_windowHandle);
}

Window::~Window()
{

}

void Window::handleEvents()
{
	// Thread messages

	MSG msg;

	while (PeekMessage(&msg,
	                0,
	                UINT(0),
	                UINT(0),
	                PM_REMOVE))
	{
		if (msg.message == WM_QUIT) // do we receive a WM_QUIT message?
		{
			/*_winEventQueue.push(WindowEvent(QUIT_REQUEST,
			                                0,
			                                0));*/
		}
		else
		{
			TranslateMessage(&msg); // translate and dispatch to event queue
			DispatchMessage(&msg);
		}
	}

}

LRESULT CALLBACK Window::windowProc(HWND hwnd,
                                    UINT msg,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			// Sets the data in create parameter to the window user data.

			CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
			Window *thiz = reinterpret_cast<Window *>(pCreate->lpCreateParams);
			SetWindowLongPtr(hwnd,
			                 GWLP_USERDATA,
			                 LONG_PTR(thiz));
			break;
		}
		case WM_ACTIVATE: // watch for the window being minimized and restored
		{
			Window *thiz = reinterpret_cast<Window *>(GetWindowLongPtr(hwnd,
			                                                           GWLP_USERDATA));

			if (!HIWORD(wParam))
			{
				/*
				thiz->_winEventQueue.push(WindowEvent(ACTIVATE,
				                                      0,
				                                      0));
				*/
			}
			else
			{
				/*
				thiz->_winEventQueue.push(WindowEvent(DEACTIVATE,
				                                      0,
				                                      0));
				*/
			}

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

		case WM_CLOSE: // window is being closed
			// send WM_QUIT to message queue
			PostQuitMessage(0);

			return 0;

		case WM_SIZE:
		{
			Window *thiz = reinterpret_cast<Window *>(GetWindowLongPtr(hwnd,
			                                                           GWLP_USERDATA));
			/*
			thiz->_winEventQueue.push(WindowEvent(RESIZE,
			                                      int(LOWORD(lParam)),
			                                      int(HIWORD(lParam))));
			*/

			return 0;
		}

		case WM_CHAR:
			switch (wParam)
			{
				case VK_SPACE:
				{
					//UpdateProjection(GL_TRUE);
					return 0;
				}
				case VK_ESCAPE:
				{
					// send WM_QUIT to message queue
					//PostQuitMessage(0);
					return 0;
				}
				default:
					break;
			}

			break;

		default:
			break;
	}

	return (DefWindowProc(hwnd,
	                      msg,
	                      wParam,
	                      lParam));
}

HWND Window::createWindowHandle(HINSTANCE hInstance, const Rect &winRect)
{
	WNDCLASSEX wc;

	// fill out the window class structure
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = Window::windowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // default icon
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // windows logo small icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // default arrow
	wc.hbrBackground = NULL; // no background needed
	wc.lpszMenuName = NULL; // no menu
	wc.lpszClassName = WIN32_WIN_CLASS_NAME;

	if (!RegisterClassEx(&wc))
	{
		throw WindowException("Unable to register window class");
	}

	// get our instance handle
	// _moduleHandle = GetModuleHandle(NULL);

	DWORD dwExStyle = WS_EX_APPWINDOW
	                  | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	// set up the window we're rendering to so that the top left corner is at (0,0)
	// and the bottom right corner is (height,width)
	RECT windowRect;
	windowRect.left = LONG(winRect.left);
	windowRect.right = LONG(winRect.left + winRect.w);
	windowRect.top = LONG(winRect.top);
	windowRect.bottom = LONG(winRect.top + winRect.h);

	// change the size of the rect to account for borders, etc. set by the style
	AdjustWindowRectEx(&windowRect,
	                   dwStyle,
	                   FALSE,
	                   dwExStyle);

	// class registered, so now create our window
	HWND hwnd = CreateWindowEx(dwExStyle,// extended style
	                           WIN32_WIN_CLASS_NAME,// class name
	                           WIN_TITLE,
	                           dwStyle
	                           | WS_CLIPCHILDREN
	                           | WS_CLIPSIBLINGS,
	                           0,
	                           0,// x,y coordinate
	                           windowRect.right
	                           - windowRect.left,// width
	                           windowRect.bottom
	                           - windowRect.top,// height
	                           NULL,// handle to parent
	                           NULL,// handle to menu
	                           hInstance,// application instance
	                           this);// Attach instance

	if (!hwnd)
	{
		throw WindowException("Cannot create window.");
	}

	return hwnd;
}

}
