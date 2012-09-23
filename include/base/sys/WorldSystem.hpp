/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "sys/System.hpp"

#include "gr/Renderer.hpp"
#include "action/Action.hpp"
#include "stream/ArrayInputStream.hpp"

namespace sys {

class WorldSystemRunner
{
public:
	WorldSystemRunner(gr::Renderer &renderer);

	bool update();

private:
	gr::Renderer &_renderer;
};

class WorldSystem : public System<
        WorldSystemRunner,
        gr::Renderer&>
{
public:
	WorldSystem(gr::Renderer &renderer, const TimeDuration &sync);

	// TODO: JUST FOR TESTING
	SystemActionQueue<
	        action::Action<WorldSystemRunner> > &actionQueue()
	{
		return _actions;
	}

};

}

#endif /* WORLDSYSTEM_HPP_ */
