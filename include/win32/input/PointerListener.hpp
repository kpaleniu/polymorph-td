/**
 * @file PointerListener.hpp
 *
 */

#ifndef POINTERLISTENER_HPP_
#define POINTERLISTENER_HPP_

namespace input {

typedef int pointer_button;
typedef int pointer_id;

class PointerListener
{
public:
	virtual ~PointerListener() {}

	virtual void onPointerDown(pointer_id id, pointer_button button, int x, int y) = 0;
	virtual void onPointerMove(pointer_id id, int dx, int dy) = 0;
	virtual void onPointerDrag(pointer_id id, int dx, int dy) = 0;
	virtual void onPointerUp(pointer_id id, int x, int y) = 0;
	virtual void onPointerZoom(int dz) = 0;
};

}


#endif /* POINTERLISTENER_HPP_ */
