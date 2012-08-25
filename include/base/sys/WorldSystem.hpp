/**
 * @file WorldSystem.hpp
 *
 */

#ifndef WORLDSYSTEM_HPP_
#define WORLDSYSTEM_HPP_

#include "sys/System.hpp"
#include "gr/Renderer.hpp"
#include "gr/Window.hpp"

namespace sys
{

	class WorldSystem : public System
	{
	public:
		WorldSystem(gr::Window::ConstructionData &winData);
		~WorldSystem();

	protected:
		void update();

	private:
		gr::Renderer _renderer;
		gr::Window _window;
	};

}

#endif /* WORLDSYSTEM_HPP_ */
