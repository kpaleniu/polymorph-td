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

namespace {

std::vector<gr::Vector2_r> createTestMap()
{
	return std::vector<gr::Vector2_r>
	{ 
		{  0.0f,  0.0f }, 
		{ -1.0f, -1.0f }, 
		{  1.0f, -1.0f },
		{  1.0f,  1.0f },
		{ -1.0f,  1.0f },
		{  0.0f,  0.0f }
	};
}

}

PlayState::PlayState(GameRunner& runner)
:	_runner(runner),
	_enemies(),
	_queuedForDestruction(),
	_gamePath(createTestMap()),
	_enemyCounter(0),
	_spawnTimer(TimeDuration::millis(2000))
{
}

PlayState::PlayState(PlayState&& other)
:	_runner(other._runner),
	_enemies(std::move(other._enemies)),
	_queuedForDestruction(std::move(other._queuedForDestruction)),
	_gamePath(std::move(other._gamePath)),
	_enemyCounter(other._enemyCounter),
	_spawnTimer(std::move(other._spawnTimer))
{
}

void PlayState::spawnEnemy(unsigned short hp)
{
	++_enemyCounter;

	_enemies.insert
	(
		std::make_pair
		(
			_enemyCounter,
			std::move
			(
				EnemyPolygon
				(
					_runner.graphicsSystem(),
					_enemyCounter,
					hp,
					_gamePath,
					this
				)
			)
		)
	);
}

void PlayState::enterState()
{
	{
		auto sceneMutator = _runner.graphicsSystem().sceneMutator();

		sceneMutator.scene.camera().projection = 
			gr::Projection::ortho(-5, 5, -5, 5, 5, -5);
	}

	_spawnTimer.action() =
		[this]{ spawnEnemy(_enemyCounter + 1); };
}

void PlayState::exitState()
{
	_enemies.clear();
	_queuedForDestruction.clear();
	_enemyCounter = 0;
	_spawnTimer.action() = std::function<void ()>();
}

void PlayState::update(TimeDuration dt)
{
	for (auto id : _queuedForDestruction)
		VERIFY(_enemies.erase(id));

	_queuedForDestruction.clear();

	_spawnTimer.update(dt);

	for (auto& idEnemyPair : _enemies)
		idEnemyPair.second.update(dt);
}

void PlayState::onReachedEnd(const EnemyPolygon& enemy)
{
	_queuedForDestruction.insert(enemy.id());
}

}