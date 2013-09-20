#ifndef PMTD_ENEMY_POLYGON_HPP_
#define PMTD_ENEMY_POLYGON_HPP_

#include "pm_td/Path.hpp"
#include "pm_td/EnemyType.hpp"

#include <sys/GraphicsSystem.hpp>
#include <gr/Scene.hpp>

#include <NonCopyable.hpp>

#include <atomic>
#include <array>
#include <vector>

namespace pm_td {

class Enemy : NonCopyable
{
public:

	class Listener
	{
	public:
		virtual void onReachedEnd(const Enemy&) = 0;
	};

	struct LayerData
	{
		unsigned short hp;
		EnemyType type;
	};

	typedef std::vector<LayerData> LayerDatas;

public:
	Enemy(polymorph::sys::GraphicsSystem& grSys,
				 std::size_t id, 
				 const Path& path,
				 LayerData data,
				 Listener* listener = nullptr);

	Enemy(polymorph::sys::GraphicsSystem& grSys,
				 std::size_t id,
				 const Path& path,
				 const LayerDatas& data,
				 Listener* listener = nullptr);

	Enemy(Enemy&& other);

	~Enemy();

	std::size_t id() const;

	void update(TimeDuration dt);

	/** 
	 * Creates and loads all meshes used by polygons with specified layer types
	 * and all meshes with lower and equal hp than the specified.
	 */
	static void loadMeshes(gr::MeshManager& meshManager, 
						   const LayerDatas& layerTypes);

private:
	class Layer
	{
	public:
		Layer(LayerData initialData_, 
			   gr::Scene<gr::Transform2>::model_id modelId_);

		LayerData initialData;

		gr::Scene<gr::Transform2>::model_id modelId;
		unsigned short hp;
	};
	
	std::vector<Layer> _layers;

	std::size_t _id;

	polymorph::sys::GraphicsSystem& _grSys;

	PathPoint _pathPoint;

	Listener* _listener;
};

}

#endif