/**
 * @file UISystem.cpp
 *
 */

#include "sys/UISystem.hpp"

#include "Assert.hpp"

namespace sys {


UISystemRunner::UISystemRunner(Window::ConstructionData& winCtorData)
: _window(winCtorData)
{
	_window.show(true);
}

UISystemRunner::UISystemRunner(UISystemRunner&& runner)
: _window(std::move(runner._window))
{
}

bool UISystemRunner::update()
{
	while (_window.inputSource().handleInput())
		;

	return true;
}

Window& UISystemRunner::window()
{
	return _window;
}

UISystem::UISystem(Window::ConstructionData& winCtorData, const TimeDuration& sync)
: System(sync, 256, winCtorData)
{
}

Window& UISystem::waitForWindow()
{
	waitForStartup();

	UISystemRunner* runner = _runnerAccess.load();
	ASSERT(runner != nullptr, "Runner has started but cannot be accessed, is the system dying?");

	return runner->window();
}

}



