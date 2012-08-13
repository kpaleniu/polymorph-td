#ifndef POLYMORPH_GAMEOBJECT_HPP
#define POLYMORPH_GAMEOBJECT_HPP

/**
 * This is a base class for all objects that are supposed to be drawn
 * on the screen.
 *
 * I assume at this point that game loop is going to using update-draw
 * idiom, so therefore it makes sense to create this interface. Rename
 * if needed. 
 */

#include "renderData.hpp"

namespace PolyMorph {

class GameEntity
{
	long				_id;
	RenderData::ptr		_renderData;
	AnimationData::ptr	_animationData;

public:
	GameEntity(long id) : _id(id) {}
	virtual ~GameEntity() {}
};

} /* namespace PolyMorph */

#endif /* POLYMORPH_GAMEOBJECT_HPP */
