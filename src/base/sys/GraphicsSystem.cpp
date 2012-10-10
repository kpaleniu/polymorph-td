/**
 * @file WorldSystem.cpp
 *
 */

#include "sys/WorldSystem.hpp"

#include "gr/Surface.hpp"

#include "Debug.hpp"

namespace sys {

GraphiscSystemRunner::GraphiscSystemRunner(gr::Renderer& renderer)
	: _renderer(renderer)
{

}

GraphiscSystemRunner::GraphiscSystemRunner(GraphiscSystemRunner&& system)
	: _renderer(system._renderer)
{
}

bool GraphiscSystemRunner::update()
{
	DEBUG_OUT("WorldSystem updateSystem");

	_renderer.clearBuffers();
	_renderer.flipBuffers();

	return true;
}

//

GraphicsSystem::GraphicsSystem(gr::Renderer& renderer, const TimeDuration &sync)
	: System(sync, 256, renderer)
{

}

}

