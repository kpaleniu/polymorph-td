/**
 * @file InputSource.hpp
 *
 */

#ifndef INPUTSOURCE_HPP_
#define INPUTSOURCE_HPP_

#include "input/SurfaceListener.hpp"
#include "input/KeyListener.hpp"
#include "input/PointerListener.hpp"

#include <Scoped.hpp>

#include <set>

namespace input {

/**
 *
 */
class InputSource
{
public:
	InputSource();
	virtual ~InputSource();

	virtual bool handleInput() = 0;

	void setSurfaceListener(SurfaceListener* listener);
	void setKeyListener(KeyListener* listener);
	void setPointerListener(PointerListener* listener);

protected:
	void notifyResize(int w, int h);
	void notifyShow();
	void notifyHide();
	void notifyQuit();

	void notifyKeyDown(key_type key);
	void notifyKeyUp(key_type key);

	void notifyPointerDown(pointer_id id, pointer_button button, long x, long y);
	void notifyPointerMove(pointer_id id, int dx, int dy);
	void notifyPointerDrag(pointer_id id, int dx, int dy);
	void notifyPointerUp(pointer_id id, pointer_button button, long x, long y);
	void notifyPointerZoom(int dz);

protected:
	SurfaceListener* 	_surfaceListener;
	KeyListener* 		_keyListener;
	PointerListener* 	_pointerListener;

};

}


#endif /* INPUTSOURCE_HPP_ */
