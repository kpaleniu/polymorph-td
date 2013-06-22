/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "sys/System.hpp"

#include "sys/Window.hpp"

#include <gr/Renderer.hpp>
#include <gr/Surface.hpp>
#include <gr/Scene.hpp>

// #include <concurrency/Task.hpp>

#include <NonCopyable.hpp>

namespace polymorph { namespace sys {

class GraphicsSystem;

class GraphicsSystemRunner : NonCopyable
{
public:
	struct ConstructionArgs
	{
		ConstructionArgs(Window& win_, 
						 GraphicsSystem* grSys_)
		:	win(win_), grSys(grSys_)
		{}

		ConstructionArgs(ConstructionArgs&& other)
		:	win(other.win), grSys(other.grSys)
		{}

		Window& win;
		GraphicsSystem* grSys;
	};

	GraphicsSystemRunner(ConstructionArgs args);
	GraphicsSystemRunner(GraphicsSystemRunner&& system);
	~GraphicsSystemRunner();

	bool update();

	gr::Renderer&	renderer();
	gr::Scene&		scene()		{ return _scene; }
	gr::Surface&	surface();

	static const char* getSystemName()
	{ return "GraphicsSystem"; }

private:
	gr::Surface& _surface;

	gr::Renderer _renderer;
	gr::Scene _scene;

	GraphicsSystem* _system;
};

class GraphicsSystem : public System<GraphicsSystemRunner>
{
public:
	friend class GraphicsSystemRunner;

	class SceneMutateScope : ::NonCopyable
	{
	public:
		SceneMutateScope(polymorph::concurrency::Mutex& mutex,
						 gr::Scene& scene_)
		:	_lockGuard(mutex), scene(scene_)
		{
		}

		SceneMutateScope(SceneMutateScope&& other)
		:	_lockGuard(std::move(other._lockGuard)),
			scene(other.scene)
		{
		}

		gr::Scene& scene;

	private:
		polymorph::concurrency::MutexLockGuard _lockGuard;
	};



	GraphicsSystem(Window& window);
	GraphicsSystem(GraphicsSystem&& grSys);


	SceneMutateScope sceneMutator()
	{
		return SceneMutateScope(_sceneTransactionMutex, _sourceScene);
	}

private:
	// Doesn't need to be a scene, could instead make changes to Runner's scene.
	gr::Scene _sourceScene; 

	polymorph::concurrency::Mutex _sceneTransactionMutex;
};

} }

#endif
