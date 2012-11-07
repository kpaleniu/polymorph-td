/**
 * @file Renderer_GL.cpp
 *
 */

#include "gr/Renderer.hpp"
#include "gr/Surface.hpp"
#include "gr/SurfaceException.hpp"

#include "gr/opengl.hpp"

#include "Assert.hpp"

namespace gr {

namespace {

void initGlew()
{
	GLenum err = glewInit();

	if (err != GLEW_OK)
		throw SurfaceException((const char*) glewGetErrorString(err));
}

}

Renderer::Renderer(Surface &surface)
:	_surface(surface),
	_debugDraw(),
	_bufferManager()
{
	_surface.activate(true);

	initGlew(); // Must be called after Surface::activate(true).
}

Renderer::Renderer(Renderer&& renderer)
:	_surface(renderer._surface) // TODO Move the rest
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

DebugDraw& Renderer::debugDraw()
{
	return _debugDraw;
}

BufferManager& Renderer::bufferManager()
{
	return _bufferManager;
}


}
