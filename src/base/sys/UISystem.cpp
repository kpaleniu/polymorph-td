/**
 * @file UISystem.cpp
 *
 */

#include "sys/UISystem.hpp"

#include "sys/Time.hpp"

#include "Assert.hpp"
#include "Debug.hpp"
#include "BuildConfig.hpp"


namespace sys {

// print tag
namespace { const char* TAG_RUNNER = "UISystemRunner";
			const char* TAG_SYSTEM = "UISystem"; }

UISystemRunner::UISystemRunner(Window::ConstructionData& winCtorData)
: _window(winCtorData),
  _grSys(_window)
{
	DEBUG_OUT(TAG_RUNNER, "Constructed");

	_window.show(true);
	_grSys.start();

	_grSys.waitForStartup();
}

UISystemRunner::UISystemRunner(UISystemRunner&& runner)
: _window(std::move(runner._window)),
  _grSys(std::move(runner._grSys))
{
	VERBOSE_OUT(TAG_RUNNER, "Moved");
}

UISystemRunner::~UISystemRunner()
{
	_grSys.interrupt();
	_grSys.join();

	DEBUG_OUT(TAG_RUNNER, "Destroyed");
}

bool UISystemRunner::update()
{
	TimeStamp start = TimeStamp::now();

	while (_window.inputSource().handleInput())
	{
		if (TimeDuration::between(start, TimeStamp::now()) > settings::uiSystemSync)
			break;
	}

	return true;
}

Window& UISystemRunner::window()
{
	return _window;
}

GraphicsSystem& UISystemRunner::graphics()
{
	return _grSys;
}


UISystem::UISystem(Window::ConstructionData& winCtorData)
: System(settings::uiSystemSync, 256, winCtorData)
{
	DEBUG_OUT(TAG_SYSTEM, "Constructed");
}

Window& UISystem::waitForWindow()
{
	waitForStartup();

	UISystemRunner* runner = _runnerAccess.load();
	ASSERT(runner != nullptr, "Runner has started but cannot be accessed, is the system dying?");

	return runner->window();
}

GraphicsSystem& UISystem::waitForGraphicsSystem()
{
	waitForStartup();

	UISystemRunner* runner = _runnerAccess.load();
	ASSERT(runner != nullptr, "Runner isn't alive");

	return runner->graphics();
}

}



