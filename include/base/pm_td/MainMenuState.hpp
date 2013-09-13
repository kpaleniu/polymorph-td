#ifndef PMTD_MAIN_MENU_STATE_HPP_
#define PMTD_MAIN_MENU_STATE_HPP_

#include "pm_td/GameState.hpp"

namespace pm_td {

class GameRunner;

class MainMenuState : NonCopyable
{
public:
	MainMenuState(GameRunner& runner);
	MainMenuState(MainMenuState&& other);

	void enterState();
	void exitState();
	void update(TimeDuration dt);

private:
	GameRunner& _runner;
};


}

#endif