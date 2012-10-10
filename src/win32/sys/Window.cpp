/**
 * @file Window.cpp
 *
 * MS Windows implementation of class Window.
 */

#include "sys/Window.hpp"
#include "sys/WindowException.hpp"
#include "Assert.hpp"
#include "BuildConfig.hpp"

// Windows XP is the minimum requirement for using raw input
static_assert(_WIN32_WINNT >= 0x0501,
	"Windows target version not supported (_WIN32_WINNT < 0x0501)");


namespace sys {
namespace {

ATOM registerClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = input::handler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance  = hInstance;
	wc.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = TEXT("wndclass");

	ATOM name = RegisterClassEx(&wc);
	if (name == 0)
		throw sys::WindowException("Unable to register window class");
	return name;
}

void recalculateRect(Window::Rect& rect, DWORD exStyle, DWORD style)
{
	RECT rc = { rect.left, rect.top, rect.left + rect.w, rect.top + rect.h };
	VERIFY(AdjustWindowRectEx(&rc, style, FALSE, exStyle));

	ASSERT(rc.right >= rc.left && rc.bottom >= rc.top,
		"window rectangle is not normalized");

	rect.left = rc.left;
	rect.top  = rc.top;
	rect.w    = rc.right - rc.left;
	rect.h    = rc.bottom - rc.top;
}

HWND createWindow(const Window::ConstructionData& desc, Window* window)
{
	HINSTANCE module = desc.hInstance ? desc.hInstance : GetModuleHandle(NULL);
	ATOM name = registerClass(module);

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	Window::Rect rect = desc.winRect;
	recalculateRect(rect, dwExStyle, dwStyle);

	HWND hwnd = CreateWindowEx(
		dwExStyle,
		MAKEINTATOM(name),
		TEXT(WIN_TITLE),
		dwStyle,
		rect.left, rect.top,
		rect.w, rect.h,
		NULL,
		NULL,
		module,
		window);	// this value is attached as user data by sys::handler

	if (!hwnd)
		throw WindowException("Cannot create window.");
	return hwnd;
}

}	// anonymous namespace

namespace detail {

void window_deleter::operator()(HWND window)
{
	VERIFY(DestroyWindow(window));
}

}	// namespace detail

Window::Window(const ConstructionData &ctorData) :
		_windowHandle(createWindow(ctorData, this)),
		_inputSource(_windowHandle.get())
{
	// get raw input data from the mouse/pointer device
	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage     = 0x02;
	rid.dwFlags     = RIDEV_INPUTSINK;
	rid.hwndTarget  = _windowHandle.get();
	VERIFY(RegisterRawInputDevices(&rid, 1, sizeof(rid)));
}

bool Window::show(bool show)
{
	BOOL wasVisible = ShowWindow(_windowHandle.get(), show ? SW_SHOW : SW_HIDE);
	if (show)
		VERIFY(UpdateWindow(_windowHandle.get()));
	return !!wasVisible;
}

input::WindowInputSource& Window::inputSource()
{
	return _inputSource;
}

HWND Window::nativeHandle()
{
	return _windowHandle.get();
}

}	// namespace sys
