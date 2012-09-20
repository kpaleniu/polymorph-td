/**
 * @file Renderer.hpp
 *
 * Contains interface and mockup implementation for class Renderer.
 */

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

namespace gr {

class Surface;

/**
 * Encapsulates rendering calls to a surface.
 *
 * Only one renderer should be used per surface.
 * This class is platform and configuration dependent.
 */
class Renderer
{
public:
	/**
	 * Constructor.
	 *
	 * @param surface Surface this renderer renders.
	 */
	Renderer(Surface &surface);
	/**
	 * Destructor.
	 */
	~Renderer();

	/**
	 * Sets the color buffer clearing value.
	 */
	void setClearColor(float r,
	                   float g,
	                   float b,
	                   float a = 1.0f);

	/**
	 * Clears all activated buffers.
	 */
	void clearBuffers();
};

}

// Mockup implementation

namespace gr {

Renderer::Renderer(Surface &)
{
	//
}

Renderer::~Renderer()
{
	//
}

void Renderer::setClearColor(float,
                             float,
                             float,
                             float)
{
	//
}

void Renderer::clearBuffers()
{
	//
}

}

#endif
