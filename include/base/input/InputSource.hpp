/**
 * @file InputSource.hpp
 *
 */

#ifndef INPUTSOURCE_HPP_
#define INPUTSOURCE_HPP_

#include "input/SurfaceListener.hpp"
#include "input/KeyListener.hpp"
#include "input/PointerListener.hpp"

#include "Scoped.hpp"

#include <set>

namespace input {

typedef Scoped SurfaceEventSubscription;
typedef Scoped KeyEventSubscription;
typedef Scoped PointerEventSubscription;


/**
 *
 */
class InputSource
{
public:
	virtual bool handleInput() = 0;
	virtual ~InputSource();

	void registerSurfaceListener(SurfaceListener& listener);
	void unregisterSurfaceListener(SurfaceListener& listener);
	SurfaceEventSubscription surfaceSubscription(SurfaceListener& listener);

	void registerKeyListener(KeyListener& listener);
	void unregisterKeyListener(KeyListener& listener);
	KeyEventSubscription keySubscription(KeyListener& listener);

	void registerPointerListener(PointerListener& listener);
	void unregisterPointerListener(PointerListener& listener);
	PointerEventSubscription pointerSubscription(PointerListener& listener);

protected:
	void notifyResize(int w, int h);
	void notifyShow();
	void notifyHide();
	void notifyDestroy();

	void notifyKeyDown(key_type key);
	void notifyKeyUp(key_type key);

	void notifyPointerDown(pointer_id id, pointer_button button, int x, int y);
	void notifyPointerMove(pointer_id id, int dx, int dy);
	void notifyPointerDrag(pointer_id id, int dx, int dy);
	void notifyPointerUp(pointer_id id, int x, int y);
	void notifyPointerZoom(int dz);

protected:
	std::set<SurfaceListener*> _surfaceListeners;
	std::set<KeyListener*> _keyListeners;
	std::set<PointerListener*> _pointerListeners;

};

}


#endif /* INPUTSOURCE_HPP_ */
