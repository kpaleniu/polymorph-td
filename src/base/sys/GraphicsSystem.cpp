/**
 * @file WorldSystem.cpp
 *
 */

#include "sys/GraphicsSystem.hpp"

#include "gr/Surface.hpp"

#include "Debug.hpp"

namespace sys {

GraphiscSystemRunner::GraphiscSystemRunner(Window& win)
	: _surface(win), _renderer(_surface)
{

}

GraphiscSystemRunner::GraphiscSystemRunner(GraphiscSystemRunner&& system)
	: _surface(std::move(system._surface)), _renderer(std::move(system._renderer))
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

GraphicsSystem::GraphicsSystem(Window& window, const TimeDuration &sync)
	: System(sync, 256, window)
{

}

}

