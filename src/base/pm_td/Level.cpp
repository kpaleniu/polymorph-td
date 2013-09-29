#include "pm_td/Level.hpp"

namespace polymorph { namespace pm_td {

namespace {

std::vector<gr::Vector2_r> createTestPath()
{
	return std::vector<gr::Vector2_r>
	{
		{ -4.0f, 4.0f },
		{ -4.0f, -4.0f },
		{ 4.0f, -4.0f },
		{ 4.0f, 4.0f },
		{ -4.0f, 4.0f },
		{ -4.0f, 4.0f }
	};
}

}


Level::Level(Level::Director* director)
:	_enemyPath(createTestPath()),
	_director(director)
{
}

Level::Level(Level && other)
:	_enemyPath(std::move(other._enemyPath)),
	_director(other._director)
{
	other._director = nullptr;
}

Level& Level::operator=(Level&& other)
{
	_enemyPath = std::move(other._enemyPath);
	_director = other._director;

	other._director = nullptr;

	return *this;
}

void Level::update(TimeDuration)
{
	// TEST TEST TEST

	static bool firstCall = true;

	if (firstCall)
	{
		if (_director)
			_director->spawnEnemy(_enemyPath, { { {7, ColorType::BLUE}, {5, ColorType::RED } } });
	}

	firstCall = false;
}

std::vector<Enemy::LayerData> Level::indexLayerData() const
{
	return { {12, ColorType::BLUE}, { 12, ColorType::RED } };
}


} }