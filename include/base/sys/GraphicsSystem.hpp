/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "sys/System.hpp"

#include <gr/Renderer.hpp>
#include <gr/Surface.hpp>

#include <concurrency/Task.hpp>

#include <NonCopyable.hpp>

#include <memory>

namespace sys {

class GraphicsSystemRunner : NonCopyable
{
public:
	GraphicsSystemRunner(Window& win);
	GraphicsSystemRunner(GraphicsSystemRunner&& system);
	~GraphicsSystemRunner();

	bool update();

	gr::Renderer& renderer();
	gr::Surface& surface();

	static const char* getSystemName()
	{ return "GraphicsSystem"; }

private:
	gr::Surface& _surface;

	gr::Renderer _renderer;
};

class GraphicsSystem : public System<GraphicsSystemRunner>
{
public:
	GraphicsSystem(Window& window);
	GraphicsSystem(GraphicsSystem&& grSys);

	SystemActionQueue<GraphicsSystemRunner>& actionQueue()
	{
		return _actions;
	}
};

}

#endif /* WORLDSYSTEM_HPP_ */
