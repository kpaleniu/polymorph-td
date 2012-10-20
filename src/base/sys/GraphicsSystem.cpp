/**
 * @file WorldSystem.cpp
 *
 */

#include "sys/GraphicsSystem.hpp"
#include "sys/Window.hpp"

#include "gr/Surface.hpp"

#include "Debug.hpp"

namespace sys {

// print tag
namespace { const char* TAG_RUNNER = "GraphicsSystemRunner";
			const char* TAG_SYSTEM = "GraphicsSystem"; }

GraphiscSystemRunner::GraphiscSystemRunner(Window& win)
: _surface(win.surface()), _renderer(_surface)
{
	_surface.activate(true);

	DEBUG_OUT(TAG_RUNNER, "Constructed");
}

GraphiscSystemRunner::GraphiscSystemRunner(GraphiscSystemRunner&& system)
: _surface(system._surface), _renderer(std::move(system._renderer))
{
	VERBOSE_OUT(TAG_RUNNER, "Moved");
}

bool GraphiscSystemRunner::update()
{
	VERBOSE_OUT(TAG_RUNNER, "update()");

	_renderer.clearBuffers();
	_renderer.flipBuffers();

	return true;
}

//

GraphicsSystem::GraphicsSystem(Window& window, const TimeDuration &sync)
: System(sync, 256, window)
{
	DEBUG_OUT(TAG_SYSTEM, "Constructed");
}

GraphicsSystem::GraphicsSystem(GraphicsSystem&& grSys)
: System(std::move(grSys))
{
	VERBOSE_OUT(TAG_SYSTEM, "Moved");
}

}

