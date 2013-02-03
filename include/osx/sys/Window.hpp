/**
 * @file Window.hpp
 * OSX (and possibly iOS) header for Window. However, this class has
 * nothing platform-specific and is basically a rip-off of the
 * win32/sys/Window.hpp, so these may be merged together some time
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "gr/Surface.hpp"
#include "input/InputSource.hpp"
#include "input/WindowInputSource.hpp"

#include <NonCopyable.hpp>

namespace sys {

struct WindowImpl;
struct AppDelegate;

class Window : NonCopyable
{
public:
	struct Rect
	{
		int left;
		int top;
		int w;
		int h;
	};
    
    struct ConstructionData
	{
		struct AppDelegate* app;
		Rect                rect;
	};

	Window(const ConstructionData& data);
	Window(Window&& window);

	~Window();

	bool show(bool show = true);

	/* OSX API event handlers */
	void applicationWillFinishLaunching();
	void applicationDidFinishLaunching();

	input::WindowInputSource& inputSource();

	gr::Surface& surface();

private:
    /* No pointer-wrapper because of C++/Obj-C mismatches */
    WindowImpl*         _impl;
    WindowInputSource   _inputSource;
    gr::Surface         _surface;
};

} /* namespace sys */

#endif /* WINDOW_HPP_ */
