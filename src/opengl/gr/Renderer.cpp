/**
 * @file Renderer_GL.cpp
 *
 */

#include "gr/Renderer.hpp"
#include "gr/Surface.hpp"
#include "gr/SurfaceException.hpp"
#include "gr/GraphicsException.hpp"

#include "gr/opengl.hpp"

#include "Assert.hpp"
#include "Debug.hpp"

namespace gr {

namespace {

void initGlew()
{
	GLenum err = glewInit();

	if (err != GLEW_OK)
		throw SurfaceException((const char*) glewGetErrorString(err));
}

const char* TAG = "Renderer";

}

Renderer::Renderer(Surface &surface)
:	_surface(surface),
	_debugDraw(),
	_bufferManager()
{
	_surface.activate(true);

	initGlew(); // Must be called after Surface::activate(true).


	int openGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &openGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &openGLVersion[1]);
	VERBOSE_OUT(TAG, "GL Version %i.%i", openGLVersion[0], openGLVersion[1]);
}

Renderer::Renderer(Renderer&& renderer)
:	_surface(renderer._surface) // TODO Move the rest
{
}

Renderer::~Renderer()
{
	VERBOSE_OUT(TAG, "dtor");
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

void Renderer::render()
{
	clearBuffers();

	_renderList.erase(
			std::remove_if(_renderList.begin(),
			               _renderList.end(),
			               [this](const RenderAction& action) -> bool
						   { return !action(*this); }),
			_renderList.end());

#ifdef _DEBUG
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
		throw GraphicsException(std::string((char*) gluErrorString(errCode)));
#endif
}

void Renderer::addRenderAction(RenderAction&& action)
{
	_renderList.push_back(action);
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
