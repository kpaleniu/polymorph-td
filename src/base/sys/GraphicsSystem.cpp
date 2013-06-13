/**
 * @file WorldSystem.cpp
 *
 */

#include "sys/GraphicsSystem.hpp"
#include "sys/Window.hpp"

#include "gr/Surface.hpp"

#include "Debug.hpp"

#include "BuildConfig.hpp"

namespace polymorph { namespace sys {

// print tag
namespace { const char* TAG_RUNNER = "GraphicsSystemRunner";
			const char* TAG_SYSTEM = "GraphicsSystem"; }

GraphicsSystemRunner::GraphicsSystemRunner(Window& win)
: _surface(win.surface()), _renderer(_surface)
{
	DEBUG_OUT(TAG_RUNNER, "Constructed");
}

GraphicsSystemRunner::GraphicsSystemRunner(GraphicsSystemRunner&& system)
: _surface(system._surface), _renderer(std::move(system._renderer))
{
	VERBOSE_OUT(TAG_RUNNER, "Moved");
}

GraphicsSystemRunner::~GraphicsSystemRunner()
{
	DEBUG_OUT(TAG_RUNNER, "Destroyed");
}

bool GraphicsSystemRunner::update()
{
	_renderer.render();

	_renderer.flipBuffers();

	return true;
}

gr::Renderer& GraphicsSystemRunner::renderer()
{
	return _renderer;
}

gr::Surface& GraphicsSystemRunner::surface()
{
	return _surface;
}

//

GraphicsSystem::GraphicsSystem(Window& window)
: System(TimeDuration::millis( 33 /*settings::sys::grSystemSyncMillis*/), 256, window)
{
	DEBUG_OUT(TAG_SYSTEM, "Constructed");
}

GraphicsSystem::GraphicsSystem(GraphicsSystem&& grSys)
: System(std::move(grSys))
{
	VERBOSE_OUT(TAG_SYSTEM, "Moved");
}

} }

