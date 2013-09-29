#include "pm_td/Path.hpp"


namespace polymorph { namespace pm_td {

namespace {

std::vector<gr::real_t> 
	createDistanceView(const std::vector<gr::Vector2_r>& checkPoints)
{
	std::vector<gr::real_t> rVec;
	rVec.reserve(checkPoints.size() - 1);

	for (std::size_t i = 0; i < checkPoints.size() - 1; ++i)
	{
		const auto& startPoint = checkPoints[i];
		const auto& endPoint = checkPoints[i + 1];

		auto diff = endPoint - startPoint;
		rVec.push_back( diff.length() );
	}

	return rVec;
}


}

PathPoint::PathPoint(const std::vector<gr::Vector2_r>& checkPoints,
					 const std::vector<gr::real_t>& distanceView,
					 gr::real_t traveled)
:	_checkPoints(checkPoints),
	_distanceView(distanceView),
	_lastCheckPointIndex(0),
	_distanceFromLastCheckPoint(0.0f)
{
	ASSERT(traveled >= 0.0f, "Expected positive distance.");

	gr::real_t currentDistance = 0.0f;

	for (std::size_t i = 0; i < _distanceView.size(); ++i)
	{
		auto dist = _distanceView[i];

		gr::real_t nextDistance = currentDistance + dist;

		if (traveled >= currentDistance && traveled < nextDistance)
		{
			_lastCheckPointIndex = i;
			_distanceFromLastCheckPoint = (traveled - currentDistance) / dist;

			currentDistance = nextDistance;

			break;
		}

		currentDistance = nextDistance;
	}

	// If traveled past end (break not called).
	if (traveled >= currentDistance)
		_lastCheckPointIndex = _checkPoints.size() - 1;
}

PathPoint::PathPoint(const PathPoint& other)
:	_checkPoints(other._checkPoints),
	_distanceView(other._distanceView),
	_lastCheckPointIndex(other._lastCheckPointIndex),
	_distanceFromLastCheckPoint(other._distanceFromLastCheckPoint)
{
}

void PathPoint::advance(gr::real_t distance)
{
	// Don't advance if passed end.
	if (_lastCheckPointIndex == _checkPoints.size() - 1)
		return;

	_distanceFromLastCheckPoint += distance;

	while (_lastCheckPointIndex < _checkPoints.size() - 1
		   && _distanceFromLastCheckPoint >= _distanceView[_lastCheckPointIndex])
	{
		_distanceFromLastCheckPoint -= _distanceView[_lastCheckPointIndex];
		++_lastCheckPointIndex;
	}
}

gr::Vector2_r PathPoint::currentPosition() const
{
	if (_lastCheckPointIndex == _checkPoints.size() - 1)
		return _checkPoints[_checkPoints.size() - 1];

	auto p0 = _checkPoints[_lastCheckPointIndex];
	auto p1 = _checkPoints[_lastCheckPointIndex + 1];

	auto percentageToNext = _distanceFromLastCheckPoint 
							/ _distanceView[_lastCheckPointIndex];

	return p0 + percentageToNext * (p1 - p0); // TODO Add lerp to math lib.
}

bool PathPoint::reachedEnd() const
{
	return _lastCheckPointIndex == _checkPoints.size() - 1;
}


Path::Path(std::vector<gr::Vector2_r> && checkPoints)
:	_checkPoints(std::move(checkPoints)),
	_distanceView(createDistanceView(_checkPoints))
{
}

PathPoint Path::getStart() const
{
	return PathPoint(_checkPoints, _distanceView);
}

} }