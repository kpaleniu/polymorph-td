#ifndef PMTD_ENEMY_POLYGON_HPP_
#define PMTD_ENEMY_POLYGON_HPP_

#include "pm_td/Path.hpp"
#include "pm_td/EnemyType.hpp"

#include <sys/GraphicsSystem.hpp>
#include <gr/Scene.hpp>

#include <NonCopyable.hpp>

#include <atomic>

namespace pm_td {

class EnemyPolygon : NonCopyable
{
public:
	class Listener
	{
	public:
		virtual void onReachedEnd(const EnemyPolygon&) = 0;
	};

	struct LayerData
	{
		unsigned short hp;
		EnemyType type;
	};

	EnemyPolygon(polymorph::sys::GraphicsSystem& grSys,
				 std::size_t id, 
				 const Path& path,
				 LayerData data,
				 Listener* listener = nullptr);

	/* 2 layers not implemented yet.
	EnemyPolygon(polymorph::sys::GraphicsSystem& grSys,
				 std::size_t id,
				 const Path& path,
				 LayerData data[2],
				 Listener* listener = nullptr);
	*/

	EnemyPolygon(EnemyPolygon&& other);

	~EnemyPolygon();

	std::size_t id() const;

	void update(TimeDuration dt);

	static void loadMeshes(polymorph::sys::GraphicsSystem& grSys);

private:
	gr::Scene<gr::Transform2>::model_id _model;
	unsigned short _hp;

	polymorph::sys::GraphicsSystem& _grSys;

	PathPoint _pathPoint;

	Listener* _listener;
};

}

#endif