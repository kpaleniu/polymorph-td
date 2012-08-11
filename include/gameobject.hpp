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

class graphicsContext;

namespace PolyMorph {

	class GameObject {
		public:
			virtual ~GameObject() {}

			virtual void draw(graphicsContext& ctx) = 0;
			virtual void update(float dt) = 0;
	};
} /* namespace PolyMorph */

#endif /* POLYMORPH_GAMEOBJECT_HPP */
