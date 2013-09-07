#include "pm_td/BeginState.hpp"

#include "pm_td/GameRunner.hpp"
#include "pm_td/MainMenuState.hpp"

namespace pm_td {

void BeginState::update(GameRunner& runner, TimeDuration /*dt*/)
{
	// TODO Do something, load persistent assets?

	runner.setState(std::shared_ptr<MainMenuState>(new MainMenuState()));
}

}