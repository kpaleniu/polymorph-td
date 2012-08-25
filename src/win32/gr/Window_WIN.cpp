/**
 * @file Window_WIN.cpp
 *
 */

#include "gr/Window.hpp"

#include "win32.hpp"

#include <windows.h>

namespace gr {
class Window::PIMPL
{
public:
	HWND windowHandle;
	HDC deviceHandle;
	HGLRC glHandle;
	HINSTANCE appHandle;
};

Window::Window(ConstructionData &data)
		: _pimpl(new PIMPL)
{
#if 0
	// get our instance handle
	_pimpl->appHandle = GetModuleHandle(NULL);

	WNDCLASSEX wc;// window class

	// fill out the window class structure
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW
	| CS_VREDRAW
	| CS_OWNDC;
	wc.lpfnWndProc = windowProc;// Fix
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = winData.mainParams.hInstance;
	wc.hIcon = LoadIcon(NULL,
			IDI_APPLICATION);// default icon
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);// windows logo small icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);// default arrow
	wc.hbrBackground = NULL;// no background needed
	wc.lpszMenuName = NULL;// no menu
	wc.lpszClassName = winClassName;

	// register the windows class
	if (!RegisterClassEx(&wc))
	{
		//throw WindowException("Unable to register the window class");
	}

	DWORD dwExStyle;
	DWORD dwStyle;

	dwExStyle = WS_EX_APPWINDOW
	| WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPEDWINDOW;

	// set up the window we're rendering to so that the top left corner is at (0,0)
	// and the bottom right corner is (height,width)
	RECT windowRect;
	windowRect.left = LONG(0);
	windowRect.right = LONG(winData.width);
	windowRect.top = LONG(0);
	windowRect.bottom = LONG(winData.height);

	// change the size of the rect to account for borders, etc. set by the style
	AdjustWindowRectEx(&windowRect,
			dwStyle,
			FALSE,
			dwExStyle);

	// class registered, so now create our window
	_windowHandle = CreateWindowEx(dwExStyle,// extended style
			winClassName,// class name
			winData.title.c_str(),// app name
			dwStyle
			| WS_CLIPCHILDREN
			| WS_CLIPSIBLINGS,// using OpenGL
			0,
			0,// x,y coordinate
			windowRect.right
			- windowRect.left,// width
			windowRect.bottom
			- windowRect.top,// height
			NULL,// handle to parent
			NULL,// handle to menu
			_appHandle,// application instance
			this);// Attach instance

	// see if our window handle is valid
	if (!_windowHandle)
	throw WindowException("Unable to create window");

	// get a device context
	_deviceHandle = GetDC(_windowHandle);

	if (!_deviceHandle)
	throw WindowException("Unable to create device context");

	// set the pixel format we want
	PIXELFORMATDESCRIPTOR pfd =
	{   sizeof(PIXELFORMATDESCRIPTOR), // size of structure
		1,// default version
		PFD_DRAW_TO_WINDOW
		|// window drawing support
		PFD_SUPPORT_OPENGL
		|// OpenGL support
		PFD_DOUBLEBUFFER,// double buffering support
		PFD_TYPE_RGBA,// RGBA color mode
		32,// 32 bit color mode
		0,
		0,
		0,
		0,
		0,
		0,// ignore color bits, non-palettized mode
		0,// no alpha buffer
		0,// ignore shift bit
		0,// no accumulation buffer
		0,
		0,
		0,
		0,// ignore accumulation bits
		16,// 16 bit z-buffer size
		8,// no stencil buffer
		0,// no auxiliary buffer
		PFD_MAIN_PLANE,// main drawing plane
		0,// reserved
		0,
		0,
		0}; // layer masks ignored

	GLuint pixelFormat;

	// FIXME Throwing exception doesn't destroy window.

	// choose best matching pixel format
	if (!(pixelFormat = ChoosePixelFormat(_deviceHandle,
							&pfd)))
	throw WindowException("Can't find an appropriate pixel format");

	// set pixel format to device context
	if (!SetPixelFormat(_deviceHandle,
					pixelFormat,
					&pfd))
	throw WindowException("Unable to set pixel format");

	// create the OpenGL rendering context
	if (!(_glHandle = wglCreateContext(_deviceHandle)))
	throw WindowException("Unable to create OpenGL rendering context");

	// now make the rendering context the active one
	if (!wglMakeCurrent(_deviceHandle,
					_glHandle))
	throw WindowException("Unable to activate OpenGL rendering context");

	// show the window in the foreground, and set the keyboard focus to it
	ShowWindow(_windowHandle, SW_SHOW);
	SetForegroundWindow (_windowHandle);
	SetFocus(_windowHandle);

	// set up the perspective for the current screen size
	//ResizeScene(width, height); // Not really needed at this time, or?
#endif
}

Window::~Window()
{

}
}
