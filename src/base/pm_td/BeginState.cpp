#include "pm_td/BeginState.hpp"

#include "pm_td/GameRunner.hpp"
#include "pm_td/MainMenuState.hpp"

namespace polymorph { namespace pm_td {

BeginState::BeginState(GameRunner& runner)
:	_runner(runner)
{
}

BeginState::BeginState(BeginState&& other)
:	_runner(other._runner)
{
}

void BeginState::enterState()
{
}

void BeginState::update(TimeDuration)
{
	_runner.setState(MainMenuState(_runner));
}

void BeginState::exitState()
{
}

} }