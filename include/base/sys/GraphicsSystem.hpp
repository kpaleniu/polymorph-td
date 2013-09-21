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
	struct ConstructionArgs : NonCopyable
	{
		ConstructionArgs(Window& win_, GraphicsSystem& grSys_);
		ConstructionArgs(ConstructionArgs&& other);

		Window& win;
		GraphicsSystem& grSys;
	};

	GraphicsSystemRunner(ConstructionArgs args, System<GraphicsSystemRunner>&);
	GraphicsSystemRunner(GraphicsSystemRunner&& system);
	~GraphicsSystemRunner();

	bool update(TimeDuration dt);

	gr::Renderer&	renderer();
	gr::Surface&	surface();

	/**
	 * Should only be accessed when scene is not being written to.
	 */
	const gr::Scene<gr::Transform2>& scene() const;

	static const char* getSystemName()
	{ return "GraphicsSystem"; }

private:
	gr::Surface& _surface;

	gr::Renderer _renderer;
	const gr::Scene<gr::Transform2>& _scene;

	GraphicsSystem& _system;
};

class GraphicsSystem : public System<GraphicsSystemRunner>
{
public:
	friend class GraphicsSystemRunner;

	class SceneMutateScope : ::NonCopyable
	{
	public:
		SceneMutateScope(polymorph::concurrency::Mutex& mutex, 
						 gr::Scene<gr::Transform2>& scene_,
						 gr::MeshManager& meshes_);
		SceneMutateScope(SceneMutateScope&& other);

		gr::Scene<gr::Transform2>& scene;
		gr::MeshManager&           meshes;

	private:
		polymorph::concurrency::MutexLockGuard _lockGuard;
	};


	GraphicsSystem(Window& window);
	GraphicsSystem(GraphicsSystem&& grSys);

	SceneMutateScope sceneMutator();
	const gr::Scene<gr::Transform2>& scene() const;

private:
	gr::MeshManager			  _meshManager;
	gr::Scene<gr::Transform2> _sourceScene;
	

	polymorph::concurrency::Mutex _sceneTransactionMutex;
};


} }

#endif
