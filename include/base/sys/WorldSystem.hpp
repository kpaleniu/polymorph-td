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

class WorldSystemRunner : NonCopyable
{
public:
	WorldSystemRunner(gr::Renderer &renderer);

	bool update();

private:
	gr::Renderer &_renderer;
};

class WorldSystem : public System<WorldSystemRunner>
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
