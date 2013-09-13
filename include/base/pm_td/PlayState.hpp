#ifndef PMTD_PLAY_STATE_HPP_
#define PMTD_PLAY_STATE_HPP_

#include "pm_td/GameState.hpp"
#include "pm_td/EnemyPolygon.hpp"
#include "pm_td/Path.hpp"

#include <gr/Scene.hpp>

#include <Timer.hpp>
#include <NonCopyable.hpp>

#include <map>
#include <set>

namespace pm_td {

class GameRunner;

class PlayState : 
	public EnemyPolygon::Listener,
	NonCopyable
{
public:
	PlayState(GameRunner& runner);
	PlayState(PlayState&& other);

	void spawnEnemy(unsigned int hp);

	void enterState();
	void exitState();
	void update(TimeDuration dt);

	void onReachedEnd(const EnemyPolygon& enemy) override;

private:
	GameRunner& _runner;

	std::map<size_t, EnemyPolygon> _enemies;
	std::set<size_t> _queuedForDestruction;

	unsigned int _enemyCounter;
	Path _gamePath;

	Timer _spawnTimer;
};


}

#endif