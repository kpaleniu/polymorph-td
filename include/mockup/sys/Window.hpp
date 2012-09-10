/**
 * @file Window.hpp
 *
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "gr/Surface.hpp"

namespace sys {

class Window
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
		const Rect winRect;
	};

public:
	Window(ConstructionData &ctorData)
	{
	}

	~Window()
	{
	}

	gr::Surface &surface()
	{
	}

	void handleEvents()
	{
	}

};

}

#endif /* WINDOW_HPP_ */
