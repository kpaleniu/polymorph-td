/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "gr/Renderer.hpp"
#include "gr/Surface.hpp"
#include "stream/ArrayInputStream.hpp"
#include "sys/System.hpp"

#include "NonCopyable.hpp"

namespace sys {

class GraphicsSystemRunner : NonCopyable
{
public:
	GraphicsSystemRunner(Window& win);
	GraphicsSystemRunner(GraphicsSystemRunner&& system);
	~GraphicsSystemRunner();

	bool update();

private:
	gr::Surface& _surface;
	gr::Renderer _renderer;
};

class GraphicsSystem : public System<GraphicsSystemRunner>
{
public:
	GraphicsSystem(Window& window, const TimeDuration &sync);
	GraphicsSystem(GraphicsSystem&& grSys);

	// TODO: JUST FOR TESTING
	SystemActionQueue<GraphicsSystemRunner>& actionQueue()
	{
		return _actions;
	}

};

}

#endif /* WORLDSYSTEM_HPP_ */
