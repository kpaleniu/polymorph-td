#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "sys/System.hpp"
#include "sys/Window.hpp"

#include <gr/Renderer.hpp>
#include <gr/Surface.hpp>
#include <gr/Scene.hpp>

#include <NonCopyable.hpp>

namespace polymorph { namespace sys {


class GraphicsSystem;

class GraphicsSystemRunner : NonCopyable
{
public:
	struct ConstructionArgs
	{
		ConstructionArgs(Window& win_, GraphicsSystem& grSys_);
		ConstructionArgs(ConstructionArgs&& other);

		Window& win;
		GraphicsSystem& grSys;
	};

	GraphicsSystemRunner(ConstructionArgs args);
	GraphicsSystemRunner(GraphicsSystemRunner&& system);
	~GraphicsSystemRunner();

	bool update();

	gr::Renderer&	renderer();
	gr::Surface&	surface();

	const gr::Scene& scene() const;

	static const char* getSystemName()
	{ return "GraphicsSystem"; }

private:
	gr::Surface& _surface;

	gr::Renderer _renderer;
	const gr::Scene& _scene;

	GraphicsSystem& _system;
};

class GraphicsSystem : public System<GraphicsSystemRunner>
{
public:
	friend class GraphicsSystemRunner;

	class SceneMutateScope : ::NonCopyable
	{
	public:
		SceneMutateScope(polymorph::concurrency::Mutex& mutex, gr::Scene& scene_);
		SceneMutateScope(SceneMutateScope&& other);

		gr::Scene& scene;

	private:
		polymorph::concurrency::MutexLockGuard _lockGuard;
	};


	GraphicsSystem(Window& window);
	GraphicsSystem(GraphicsSystem&& grSys);

	SceneMutateScope sceneMutator();
	const gr::Scene& scene() const;

private:
	gr::Scene _sourceScene;

	polymorph::concurrency::Mutex _sceneTransactionMutex;
};


} }

#endif
