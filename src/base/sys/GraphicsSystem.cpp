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

GraphicsSystemRunner::ConstructionArgs::ConstructionArgs(Window& win_, GraphicsSystem& grSys_)
:	win(win_), grSys(grSys_)
{
}

GraphicsSystemRunner::ConstructionArgs::ConstructionArgs(ConstructionArgs&& other)
:	win(other.win), grSys(other.grSys)
{
}


GraphicsSystemRunner::GraphicsSystemRunner(ConstructionArgs args, System<GraphicsSystemRunner>&)
:	_surface(args.win.surface()), 
	_renderer(_surface), 
	_scene(args.grSys._sourceScene),
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

bool GraphicsSystemRunner::update(TimeDuration)
{
	{
		polymorph::concurrency::MutexLockGuard sceneLock(_system._sceneTransactionMutex);
		_scene.render(_renderer);
	}

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

const gr::Scene& GraphicsSystemRunner::scene() const
{
	return _scene;
}

//

GraphicsSystem::SceneMutateScope::SceneMutateScope(polymorph::concurrency::Mutex& mutex, 
												   gr::Scene& scene_)
:	_lockGuard(mutex), scene(scene_)
{
}

GraphicsSystem::SceneMutateScope::SceneMutateScope(
	GraphicsSystem::SceneMutateScope&& other)
:	_lockGuard(std::move(other._lockGuard)), scene(other.scene)
{
}


GraphicsSystem::GraphicsSystem(Window& window)
:	System(TimeDuration::millis( 33 /*settings::sys::grSystemSyncMillis*/), 
		   256, 
		   GraphicsSystemRunner::ConstructionArgs(window, *this))
{
	DEBUG_OUT(TAG_SYSTEM, "Constructed");
}

GraphicsSystem::GraphicsSystem(GraphicsSystem&& grSys)
: System(std::move(grSys))
{
	VERBOSE_OUT(TAG_SYSTEM, "Moved");
}

GraphicsSystem::SceneMutateScope GraphicsSystem::sceneMutator()
{
	return SceneMutateScope(_sceneTransactionMutex, _sourceScene);
}

const gr::Scene& GraphicsSystem::scene() const
{
	return _sourceScene;
}


} }

