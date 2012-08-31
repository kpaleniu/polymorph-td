/**
 * @file Window.hpp
 *
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "gr/Surface.hpp"

#include <windows.h>

namespace sys {

class Window
{
public:
	struct ConstructionData
	{
		HINSTANCE hInstance;
		HINSTANCE hPrevInstance;
		LPSTR lpCmdLine;
		int nShowCmd;
	};
public:
	Window(ConstructionData &winData);

	~Window();

	gr::Surface &surface()
	{
		return _surface;
	}

public:
	// Win32 specific methods.

	const HWND getWindowHandle()
	{
		return _windowHandle;
	}

private:
	static LRESULT CALLBACK windowProc(HWND hwnd,
	                                   UINT msg,
	                                   WPARAM wParam,
	                                   LPARAM lParam);

	HWND createWindowHandle(HINSTANCE hInstance,
	                        LPCTSTR winClassName);

private:
	const HWND _windowHandle; // Must be before _surface.
	gr::Surface _surface;
};

}

#endif /* WINDOW_HPP_ */
