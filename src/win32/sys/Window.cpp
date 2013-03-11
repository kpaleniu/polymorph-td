/**
 * @file Window.cpp
 *
 * MS Windows implementation of class Window.
 */

#include "sys/Window.hpp"
#include "sys/WindowException.hpp"
#include <Assert.hpp>
#include <BuildConfig.hpp>

#include <algorithm>

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
		TEXT(settings::window::windowTitle),
		dwStyle,
		rect.left, rect.top,
		rect.w, rect.h,
		NULL,
		NULL,
		module,
		&window->inputSource());	// this value is attached as user data by sys::handler

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
		_surface(_windowHandle.get()),
		_inputSource(_windowHandle.get())
{
}

Window::Window(Window&& window) :
		_windowHandle(std::move(window._windowHandle)),
		_surface(std::move(window._surface)),
		_inputSource(window._inputSource),
		_dialogs()
{
}

bool Window::show(bool show)
{
	BOOL wasVisible = ShowWindow(_windowHandle.get(), show ? SW_SHOW : SW_HIDE);
	if (show)
		VERIFY(UpdateWindow(_windowHandle.get()));
	return !!wasVisible;
}

void Window::showMessageDialog(const std::string& title,
							   const std::string& message,
							   os::MessageDialog::Buttons buttons,
							   os::MessageDialog::Type type,
							   os::MessageDialog::Action action)
{
	// Remove old inactive dialogs:
	for (auto it = _dialogs.begin(); it != _dialogs.end();)
	{
		if (it->isFinished())
			_dialogs.erase(it++);
		else
			++it;
	}
	//

	os::MessageDialog dialog(title,
							 message,
							 buttons,
							 type,
							 action,
							 _windowHandle.get());

	dialog.show();

	_dialogs.insert( std::move(dialog) );
}

input::WindowInputSource& Window::inputSource()
{
	return _inputSource;
}

gr::Surface& Window::surface()
{
	return _surface;
}

HWND Window::nativeHandle()
{
	return _windowHandle.get();
}

}	// namespace sys
