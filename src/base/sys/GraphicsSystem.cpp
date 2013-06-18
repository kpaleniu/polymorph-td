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

GraphicsSystemRunner::GraphicsSystemRunner(ConstructionArgs args)
:	_surface(args.win.surface()), 
	_renderer(_surface), 
	_scene(),
	_system(args.grSys)
{
	DEBUG_OUT(TAG_RUNNER, "Constructed");
}

GraphicsSystemRunner::GraphicsSystemRunner(GraphicsSystemRunner&& system)
:	_surface(system._surface), 
	_renderer(std::move(system._renderer)), 
	_scene(std::move(system._scene)),
	_system(system._system)
{
	VERBOSE_OUT(TAG_RUNNER, "Moved");
}

GraphicsSystemRunner::~GraphicsSystemRunner()
{
	DEBUG_OUT(TAG_RUNNER, "Destroyed");
}

bool GraphicsSystemRunner::update()
{
	{
		polymorph::concurrency::MutexLockGuard sceneLock(_system->_sceneTransactionMutex);
		_scene = _system->_sourceScene;
	}

	_scene.render(_renderer);
	_renderer.render();

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
:	System(TimeDuration::millis( 33 /*settings::sys::grSystemSyncMillis*/), 
		   256, 
		   GraphicsSystemRunner::ConstructionArgs(window, this))
{
	DEBUG_OUT(TAG_SYSTEM, "Constructed");
}

GraphicsSystem::GraphicsSystem(GraphicsSystem&& grSys)
: System(std::move(grSys))
{
	VERBOSE_OUT(TAG_SYSTEM, "Moved");
}

} }

