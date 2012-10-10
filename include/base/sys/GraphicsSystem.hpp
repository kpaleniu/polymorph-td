/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "NonCopyable.hpp"
#include "action/Action.hpp"
#include "gr/Renderer.hpp"
#include "stream/ArrayInputStream.hpp"
#include "sys/System.hpp"

namespace sys {

class GraphiscSystemRunner : NonCopyable
{
public:
	GraphiscSystemRunner(gr::Renderer &renderer);
	GraphiscSystemRunner(GraphiscSystemRunner&& system);

	bool update();

private:
	gr::Renderer &_renderer;
};

class GraphicsSystem : public System<GraphiscSystemRunner>
{
public:
	GraphicsSystem(gr::Renderer &renderer, const TimeDuration &sync);

	// TODO: JUST FOR TESTING
	SystemActionQueue<
	        action::Action<GraphiscSystemRunner> > &actionQueue()
	{
		return _actions;
	}

};

}

#endif /* WORLDSYSTEM_HPP_ */
