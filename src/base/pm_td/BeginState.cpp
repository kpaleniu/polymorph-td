#include "pm_td/BeginState.hpp"

#include "pm_td/GameRunner.hpp"
#include "pm_td/MainMenuState.hpp"

namespace pm_td {

BeginState::BeginState(GameRunner& runner)
:	_runner(runner)
{
}

void BeginState::enterState()
{
}

void BeginState::update(TimeDuration /*dt*/)
{
	_runner.setState(MainMenuState(_runner));
}

void BeginState::exitState()
{
}

}