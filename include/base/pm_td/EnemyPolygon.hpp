#ifndef PMTD_ENEMY_POLYGON_HPP_
#define PMTD_ENEMY_POLYGON_HPP_

#include "pm_td/Path.hpp"

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

	EnemyPolygon(polymorph::sys::GraphicsSystem& grSys,
				 std::size_t id, 
				 unsigned int hp,
				 const Path& path,
				 Listener* listener = nullptr);

	EnemyPolygon(EnemyPolygon&& other);

	~EnemyPolygon();

	const std::size_t id() const;

	void update(TimeDuration dt);

	static void loadMeshes(polymorph::sys::GraphicsSystem& grSys);

private:
	gr::Scene<gr::Transform2>::model_id _model;
	unsigned int _hp;

	polymorph::sys::GraphicsSystem& _grSys;

	PathPoint _pathPoint;

	Listener* _listener;
};

}

#endif