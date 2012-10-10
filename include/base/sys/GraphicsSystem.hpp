/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "NonCopyable.hpp"
#include "action/Action.hpp"
#include "gr/Renderer.hpp"
#include "gr/Surface.hpp"
#include "stream/ArrayInputStream.hpp"
#include "sys/System.hpp"

namespace sys {

class GraphiscSystemRunner : NonCopyable
{
public:
	GraphiscSystemRunner(Window& win);
	GraphiscSystemRunner(GraphiscSystemRunner&& system);

	bool update();

private:
	gr::Surface _surface;
	gr::Renderer _renderer;
};

class GraphicsSystem : public System<GraphiscSystemRunner>
{
public:
	GraphicsSystem(Window& window, const TimeDuration &sync);

	// TODO: JUST FOR TESTING
	SystemActionQueue<
	        action::Action<GraphiscSystemRunner> > &actionQueue()
	{
		return _actions;
	}

};

}

#endif /* WORLDSYSTEM_HPP_ */
