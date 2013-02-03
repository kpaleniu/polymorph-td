/**
 * @file cocoa window class wrapper
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

namespace sys {

struct WindowImpl;

class Window {
	WindowImpl _impl;

public:
	Window();
	~Window();

	struct Rect
	{
		int left;
		int top;
		int w;
		int h;
	};

	bool show(bool show = true);

	/**
	 * Access to window input.
	 * @return	Reference to the input source active on this window.
	 */
	input::WindowInputSource& inputSource();

	gr::Surface& surface();
};

}

#endif /* WINDOW_HPP_ */
