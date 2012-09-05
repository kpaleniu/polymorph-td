/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "sys/System.hpp"

#include "gr/Renderer.hpp"
#include "sys/Window.hpp"

namespace sys
{
	class WorldSystemRunner
	{
	public:
		WorldSystemRunner(sys::Window::ConstructionData &winData);

		bool update();

	private:
		sys::Window _window;
		gr::Renderer _renderer;
	};

	typedef System<WorldSystemRunner, sys::Window::ConstructionData &> WorldSystem;
}

#endif /* WORLDSYSTEM_HPP_ */
