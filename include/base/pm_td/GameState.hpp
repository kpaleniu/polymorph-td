#ifndef PMTD_GAME_STATE_HPP_
#define PMTD_GAME_STATE_HPP_

#include <text/util.hpp>
#include <Time.hpp>

#include <memory>

namespace pm_td {

class GameRunner;

class GameState
{
public:
	virtual ~GameState() {}

	virtual void enterState(GameRunner& runner) {}
	virtual void exitState(GameRunner& runner) {}

	virtual void update(GameRunner& runner, TimeDuration dt) = 0;
};


}

#endif