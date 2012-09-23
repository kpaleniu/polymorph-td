/**
 * @file Renderer_GL.cpp
 *
 */

#include "gr/Renderer.hpp"
#include "gr/Surface.hpp"

#include <gl/gl.h>

namespace gr {

Renderer::Renderer(Surface &surface)
: _surface(surface)
{

}

Renderer::~Renderer()
{

}

void Renderer::setClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::clearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::flipBuffers()
{
	_surface.flipBuffers();
}

}
