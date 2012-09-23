/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "sys/System.hpp"
#include "sys/Window.hpp"

#include "gr/Renderer.hpp"
#include "action/Action.hpp"
#include "stream/ArrayInputStream.hpp"

namespace sys {

class WorldSystemRunner
{
public:
	WorldSystemRunner(sys::Window::ConstructionData &winData);

	bool update();

private:
	sys::Window _window;
	gr::Renderer _renderer;
};

}

namespace sys {

class WorldSystem : public System<
        WorldSystemRunner,
        sys::Window::ConstructionData &>
{
public:
	WorldSystem(const TimeDuration &sync,
	            sys::Window::ConstructionData &runnerData);

	// TODO: JUST FOR TESTING
	SystemActionQueue<
	        action::Action<WorldSystemRunner> > &actionQueue()
	{
		return _actions;
	}

};

}

#endif /* WORLDSYSTEM_HPP_ */
