/**
 * @file Surface.hpp
 *
 * Contains interface and mockup implementation for class Surface.
 */

#ifndef SURFACE_HPP_
#define SURFACE_HPP_

namespace sys {
class Window;
}

namespace gr {

/**
 * Window surface class.
 *
 * This class encapsulates a graphics context.
 * This class is platform and configuration dependent.
 */
class Surface
{
public:
	/**
	 * Constructor.
	 * @param win Window this surface belongs to.
	 */
	Surface(sys::Window &win);
	/**
	 * Destructor.
	 */
	~Surface();

	/**
	 * Flips / swaps buffers.
	 */
	void flipBuffers();
};

}

// Mockup implementation

namespace gr {

Surface::Surface(sys::Window &)
{
	//
}

Surface::~Surface()
{
	//
}

void Surface::flipBuffers()
{
	//
}

}

#endif /* SURFACE_HPP_ */
