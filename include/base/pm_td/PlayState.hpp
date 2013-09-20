#ifndef PMTD_PLAY_STATE_HPP_
#define PMTD_PLAY_STATE_HPP_

#include "pm_td/GameState.hpp"
#include "pm_td/EnemyPolygon.hpp"
#include "pm_td/Path.hpp"
#include "pm_td/Level.hpp"

#include <gr/Scene.hpp>

#include <Timer.hpp>
#include <NonCopyable.hpp>

#include <map>
#include <set>

namespace pm_td {

class GameRunner;

class PlayState : 
	public EnemyPolygon::Listener,
	public Level::Director,
	NonCopyable
{
public:
	PlayState(GameRunner& runner);
	PlayState(PlayState&& other);

	void enterState();
	void exitState();
	void update(TimeDuration dt);

	void onReachedEnd(const EnemyPolygon& enemy) override;
	void spawnEnemy(const Path& path,
					const EnemyPolygon::LayerDatas& layerData) override;

private:
	GameRunner& _runner;

	std::map<size_t, EnemyPolygon> _enemies;
	std::set<size_t> _queuedForDestruction;

	unsigned short _enemyCounter;
	Level _level;
};


}

#endif