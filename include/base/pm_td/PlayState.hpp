#pragma once

#include "pm_td/GameState.hpp"
#include "pm_td/Enemy.hpp"
#include "pm_td/Path.hpp"
#include "pm_td/Level.hpp"

#include "pm_td/Tower.hpp"

#include <gr/Scene.hpp>

#include <Timer.hpp>
#include <NonCopyable.hpp>

#include <map>
#include <set>

namespace polymorph { namespace pm_td {

class GameRunner;

class PlayState : 
	public Enemy::Listener,
	public Level::Director,
	NonCopyable
{
public:
	PlayState(GameRunner& runner);
	PlayState(PlayState&& other);

	void enterState();
	void exitState();
	void update(TimeDuration dt);

	void onReachedEnd(const Enemy& enemy) override;
	void spawnEnemy(const Path& path,
					const Enemy::LayerDatas& layerData) override;

private:
	GameRunner& _runner;

	std::map<size_t, Enemy> _enemies;
	std::set<size_t> _queuedForDestruction;

	std::map<size_t, Tower> _towers;

	unsigned short _objectCounter;
	Level _level;
};


} }