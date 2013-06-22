
#include "gr/TestWindow.hpp"

#include <gr/SurfaceException.hpp>
#include <gr/opengl.hpp>

namespace {

HWND g_hwnd;


LRESULT CALLBACK handler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		case WM_ACTIVATE:
			return 0;

		case WM_CLOSE:
			// TODO: show confirmation dialog?
			PostQuitMessage(0);
			return 0;
		default:
			break;
	}

	// allow the default event handler to process the message
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


ATOM registerClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = handler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance  = hInstance;
	wc.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = TEXT("testwndclass");

	ATOM name = RegisterClassEx(&wc);

	return name;
}

void recalculateRect(RECT& rc, DWORD exStyle, DWORD style)
{
	//RECT rc = { rect.left, rect.top, rect.left + rect.w, rect.top + rect.h };
	AdjustWindowRectEx(&rc, style, FALSE, exStyle);
}

HWND createWindow(HINSTANCE hinstance)
{
	HINSTANCE module = hinstance ? hinstance : GetModuleHandle(NULL);
	ATOM name = registerClass(module);

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	RECT rect;
	rect.left 	= 100L;
	rect.bottom = 100L;
	rect.right 	= 800L;
	rect.top 	= 600L;

	recalculateRect(rect, dwExStyle, dwStyle);

	HWND hwnd = CreateWindowEx(
		dwExStyle,
		MAKEINTATOM(name),
		TEXT("Test Window"),
		dwStyle,
		rect.left, rect.top,
		rect.right - rect.left, rect.top - rect.bottom,
		NULL,
		NULL,
		module,
		NULL);

	return hwnd;
}

}

void createTestWindow(HINSTANCE hinstance)
{
	g_hwnd = createWindow(hinstance);
	if (g_hwnd)
		ShowWindow(g_hwnd, SW_SHOW);

}

gr::Surface createSurface()
{
	auto surface = gr::Surface(g_hwnd);
	surface.activate();

	GLenum err = glewInit();
	if (err != GLEW_OK)
		throw gr::SurfaceException(); // ((const char*) glewGetErrorString(err));

	return surface;
}

void destroyTestWindow()
{
	DestroyWindow(g_hwnd);
	g_hwnd = 0;
}

bool updateTestWindow()
{
	UpdateWindow(g_hwnd);

	MSG msg;
	while (PeekMessage(&msg, g_hwnd, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true; // More messages might be in queue.
}

