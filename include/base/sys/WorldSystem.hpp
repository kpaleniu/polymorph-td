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

	class WorldSystem : public System
	{
	public:
		WorldSystem(sys::Window::ConstructionData &winData);
		~WorldSystem();

	protected:
		void update();

	private:
		sys::Window _window;
		gr::Renderer _renderer;
	};

}

#endif /* WORLDSYSTEM_HPP_ */
