/**
 * @file Renderer_GL.cpp
 *
 */

#include "gr/Renderer.hpp"
#include "gr/Surface.hpp"
#include "gr/SurfaceException.hpp"
#include "gr/GraphicsException.hpp"

#include "gr/opengl.hpp"

#include <Assert.hpp>
#include <Debug.hpp>

namespace gr {

namespace {

void initGlew()
{
	GLenum err = glewInit();

	if (err != GLEW_OK)
		throw SurfaceException(); // ((const char*) glewGetErrorString(err));
}

const char* TAG = "Renderer";

}

Renderer::Renderer(Surface &surface)
:	_surface(surface),
	_debugDraw(),
	_renderPassManager()
{
	_surface.setActive();
	_surface.setVSync();

	initGlew(); // Must be called after Surface::activate(true).


	int openGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &openGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &openGLVersion[1]);
	VERBOSE_OUT(TAG, "GL Version %i.%i", openGLVersion[0], openGLVersion[1]);
}

Renderer::Renderer(Renderer&& renderer)
:	_surface(renderer._surface),
 	_debugDraw(),
 	_renderPassManager(std::move(renderer._renderPassManager))
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

void Renderer::flipBuffers()
{
	_surface.flipBuffers();
}

void Renderer::render()
{
	_renderPassManager.render();
	_renderPassManager.clear();
	_surface.flipBuffers();

	gl::clear(GL_COLOR_BUFFER_BIT);

#ifdef _DEBUG
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
		throw GraphicsException(); //(std::string((char*) gluErrorString(errCode)));
#endif
}

DebugDraw& Renderer::debugDraw()
{
	return _debugDraw;
}

RenderPassManager& Renderer::renderPassManager()
{
	return _renderPassManager;
}


}
