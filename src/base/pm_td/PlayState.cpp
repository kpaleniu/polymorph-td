#include "pm_td/PlayState.hpp" 

#include "pm_td/GameRunner.hpp"

#include <Assert.hpp>

#include <text/util.hpp>
#include <gr/Mesh.hpp>

#include <Assert.hpp>
#include <Debug.hpp>

#include <vector>
#include <cmath>

#include <algorithm>

namespace pm_td {

PlayState::PlayState(GameRunner& runner)
:	_runner(runner),
	_enemies(),
	_queuedForDestruction(),
	_enemyCounter(0),
	_level()
{
}

PlayState::PlayState(PlayState&& other)
:	_runner(other._runner),
	_enemies(std::move(other._enemies)),
	_queuedForDestruction(std::move(other._queuedForDestruction)),
	_enemyCounter(other._enemyCounter),
	_level(std::move(other._level))
{
}



void PlayState::enterState()
{
	_level = Level(this);

	{
		auto sceneMutator = _runner.graphicsSystem().sceneMutator();

		sceneMutator.scene.camera().projection = 
			gr::Projection::ortho(-5, 5, -5, 5, 5, -5);

		Enemy::loadMeshes(sceneMutator.meshes, _level.indexLayerData());
	}
}

void PlayState::exitState()
{
	_enemies.clear();
	_queuedForDestruction.clear();
	_enemyCounter = 0;
}

void PlayState::update(TimeDuration dt)
{
	for (auto id : _queuedForDestruction)
		VERIFY(_enemies.erase(id));

	_queuedForDestruction.clear();

	_level.update(dt);

	for (auto& idEnemyPair : _enemies)
		idEnemyPair.second.update(dt);
}

void PlayState::onReachedEnd(const Enemy& enemy)
{
	_queuedForDestruction.insert(enemy.id());
}

void PlayState::spawnEnemy(const Path& path,
						   const Enemy::LayerDatas& layerData)
{
	++_enemyCounter;

	_enemies.insert
	(
		std::make_pair
		(
			_enemyCounter,
			std::move
			(
				Enemy
				(
					_runner.graphicsSystem(),
					_enemyCounter,
					path,
					layerData,
					this
				)
			)
		)
	);
}

}