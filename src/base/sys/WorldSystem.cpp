/**
 * @file WorldSystem.cpp
 *
 */

#include "sys/WorldSystem.hpp"

#include "gr/Surface.hpp"

#include "Debug.hpp"

namespace sys {

WorldSystemRunner::WorldSystemRunner(gr::Renderer& renderer)
	: _renderer(renderer)
{

}

WorldSystemRunner::WorldSystemRunner(WorldSystemRunner&& system)
	: _renderer(system._renderer)
{
}

bool WorldSystemRunner::update()
{
	DEBUG_OUT("WorldSystem updateSystem");

	_renderer.clearBuffers();
	_renderer.flipBuffers();

	return true;
}

//

WorldSystem::WorldSystem(gr::Renderer& renderer, const TimeDuration &sync)
	: System(sync, 256, renderer)
{

}

}

