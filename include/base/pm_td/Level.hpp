#ifndef PMTD_LEVEL_HPP_
#define PMTD_LEVEL_HPP_

#include "pm_td/EnemyPolygon.hpp"
#include "pm_td/Path.hpp"

#include <NonCopyable.hpp>

#include <vector>

namespace pm_td {

class Level : NonCopyable
{
public:
	class Director
	{
	public:
		virtual void spawnEnemy(const Path& path, 
								const EnemyPolygon::LayerDatas& layerData) = 0;
	};

public:
	Level(Director* director = nullptr);
	Level(Level&& other);

	Level& operator=(Level&& other);

	void update(TimeDuration dt);

	/**
	 * Returns all polygon layer types used in level.
	 *
	 * Note, this will iterate through all possible spawning enemies so
	 * you should buffer the return value.
	 */
	std::vector<EnemyPolygon::LayerData> indexLayerData() const;

private:
	
	Path _enemyPath;
	Director* _director;
};

}

#endif