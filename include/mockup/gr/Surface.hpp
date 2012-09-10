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
	Surface(sys::Window &win)
	{
	}
	~Surface()
	{
	}

	void flipBuffers()
	{
	}
};

}

#endif /* SURFACE_HPP_ */
