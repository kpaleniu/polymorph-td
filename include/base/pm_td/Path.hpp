#ifndef PMTD_PATH_HPP_
#define PMTD_PATH_HPP_

#include <gr/types.hpp>

#include <vector>

namespace pm_td {

class PathPoint
{
public:
	PathPoint(const std::vector<gr::Vector2_r>& checkPoints,
			  const std::vector<gr::real_t>& distanceView,
			  gr::real_t traveled = 0.0f);

	PathPoint(const PathPoint& other);

	void advance(gr::real_t distance);

	gr::Vector2_r currentPosition() const;

	bool reachedEnd() const;

private:
	PathPoint& operator=(const PathPoint&);

	const std::vector<gr::Vector2_r>& _checkPoints;
	const std::vector<gr::real_t>& _distanceView;

	std::size_t _lastCheckPointIndex;
	gr::real_t  _distanceFromLastCheckPoint;
};

class Path
{
public:
	Path(std::vector<gr::Vector2_r>&& checkPoints);

	PathPoint getStart() const;


private:
	std::vector<gr::Vector2_r> _checkPoints;
	std::vector<gr::real_t> _distanceView;
};

}

#endif