#ifndef PMTD_BEGIN_STATE_HPP_
#define PMTD_BEGIN_STATE_HPP_

#include "pm_td/GameState.hpp"

namespace pm_td {

class BeginState : public GameState
{
public:
	void update(GameRunner& runner, TimeDuration dt);
};

}

#endif