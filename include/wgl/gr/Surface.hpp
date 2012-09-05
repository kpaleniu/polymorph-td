/**
 * @file Surface.hpp
 *
 */

#ifndef SURFACE_HPP_
#define SURFACE_HPP_

namespace sys {
class Window;
}

#include <windows.h>
#include <wingdi.h>

namespace gr {

/**
 *
 */
class Surface
{
public:
	Surface(sys::Window &win);
	~Surface();

	void flipBuffers();

private:
	sys::Window &_win;

	HGLRC _glHandle;
	HDC _deviceHandle;
};

}

#endif /* SURFACE_HPP_ */
