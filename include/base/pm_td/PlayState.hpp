#ifndef PMTD_PLAY_STATE_HPP_
#define PMTD_PLAY_STATE_HPP_

#include "pm_td/GameState.hpp"

#include <gr/Scene.hpp>

#include <atomic>

namespace pm_td {

class PlayState : public GameState
{
public:
	void enterState(GameRunner& runner);
	void exitState(GameRunner& runner);
	void update(GameRunner& runner, TimeDuration dt);

private:
	std::atomic_bool _initialized;
};


}

#endif