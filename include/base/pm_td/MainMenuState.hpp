#ifndef PMTD_MAIN_MENU_STATE_HPP_
#define PMTD_MAIN_MENU_STATE_HPP_

#include "pm_td/GameState.hpp"

namespace pm_td {

class MainMenuState : public GameState
{
public:
	void enterState(GameRunner& runner);
	void exitState(GameRunner& runner);
	void update(GameRunner& runner, TimeDuration dt);
};


}

#endif