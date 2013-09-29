#include "pm_td/PlayState.hpp" 

#include "pm_td/GameRunner.hpp"

#include <Assert.hpp>

#include <gr/Mesh.hpp>

#include <sys/Systems.hpp>

#include <Assert.hpp>
#include <Debug.hpp>

#include <vector>
#include <cmath>

#include <algorithm>

namespace polymorph { namespace pm_td {

PlayState::PlayState(GameRunner& runner)
:	_runner(runner),
	_enemies(),
	_queuedForDestruction(),
	_towers(),
	_objectCounter(0),
	_level()
{
}

PlayState::PlayState(PlayState && other)
:	_runner(other._runner),
	_enemies(std::move(other._enemies)),
	_queuedForDestruction(std::move(other._queuedForDestruction)),
	_towers(std::move(other._towers)),
	_objectCounter(other._objectCounter),
	_level(std::move(other._level))
{
}



void PlayState::enterState()
{
	_level = Level(this);

	_runner.gameScene().camera().projection = 
		gr::Projection::ortho(-5, 5, -5, 5, 5, -5);

	Enemy::loadMeshes(_runner.gameScene(), _level.indexLayerData());
	
	// TEST

	++_objectCounter;

	_towers.insert
	(
		std::make_pair
		(
			_objectCounter,
			Tower
			(
				_runner.gameScene(),
				{
					1,
					ColorType::RED
				},
				_objectCounter,
				TimeDuration::millis(500)
			)
		)
	);
}

void PlayState::exitState()
{
	_enemies.clear();
	_queuedForDestruction.clear();
	_objectCounter = 0;
}

void PlayState::update(TimeDuration dt)
{
	for (auto id : _queuedForDestruction)
		VERIFY(_enemies.erase(id));

	_queuedForDestruction.clear();

	_level.update(dt);

	for (auto& idEnemyPair : _enemies)
		idEnemyPair.second.update(dt);

	for (auto& idTowerPair : _towers)
		idTowerPair.second.update(dt);
}

void PlayState::onReachedEnd(const Enemy& enemy)
{
	_queuedForDestruction.insert(enemy.id());
}

void PlayState::spawnEnemy(const Path& path,
						   const Enemy::LayerDatas& layerData)
{
	++_objectCounter;

	_enemies.insert
	(
		std::make_pair
		(
			_objectCounter,
			std::move
			(
				Enemy
				(
					_runner.gameScene(),
					1.5f,
					_objectCounter,
					path,
					layerData,
					this
				)
			)
		)
	);
}

} }