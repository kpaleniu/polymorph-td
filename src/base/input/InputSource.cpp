/**
 * @file InputSource.cpp
 *
 */

#include "input/InputSource.hpp"

#include "Assert.hpp"

#include <algorithm>

namespace input {

InputSource::~InputSource()
{
}

void InputSource::registerSurfaceListener(SurfaceListener& listener)
{
#ifdef _DEBUG
	ASSERT(_surfaceListeners.find(&listener) == _surfaceListeners.end(),
	       "Listener already registered");
#endif

	_surfaceListeners.insert(&listener);
}

void InputSource::unregisterSurfaceListener(SurfaceListener& listener)
{
#ifdef _DEBUG
	ASSERT(_surfaceListeners.erase(&listener) == 1,
	       "Listener not registered");
#else
	_surfaceListeners.erase(&listener);
#endif
}

SurfaceEventSubscription InputSource::surfaceSubscription(SurfaceListener& listener)
{
	return SurfaceEventSubscription([&] { registerSurfaceListener(listener); },
	                                [&] { unregisterSurfaceListener(listener); });
}

void InputSource::registerKeyListener(KeyListener& listener)
{
#ifdef _DEBUG
	ASSERT(_keyListeners.find(&listener) == _keyListeners.end(),
	       "Listener already registered");
#endif

	_keyListeners.insert(&listener);
}

void InputSource::unregisterKeyListener(KeyListener& listener)
{
#ifdef _DEBUG
	ASSERT(_keyListeners.erase(&listener) == 1,
	       "Listener not registered");
#else
	_keyListeners.erase(&listener);
#endif
}

KeyEventSubscription InputSource::keySubscription(KeyListener& listener)
{
	return KeyEventSubscription([&]	{ registerKeyListener(listener); },
	                            [&] { unregisterKeyListener(listener); });
}

void InputSource::registerPointerListener(PointerListener& listener)
{
#ifdef _DEBUG
	ASSERT(_pointerListeners.find(&listener) == _pointerListeners.end(),
	       "Listener already registered");
#endif

	_pointerListeners.insert(&listener);
}

void InputSource::unregisterPointerListener(PointerListener& listener)
{
#ifdef _DEBUG
	ASSERT(_pointerListeners.erase(&listener) == 1,
	       "Listener not registered");
#else
	_pointerListeners.erase(&listener);
#endif
}

PointerEventSubscription InputSource::pointerSubscription(PointerListener& listener)
{
	return PointerEventSubscription([&]	{ registerPointerListener(listener); },
	                                [&] { unregisterPointerListener(listener); });
}

void InputSource::notifyResize(int w, int h)
{
	std::for_each(_surfaceListeners.begin(),
	              _surfaceListeners.end(),
	              [&](SurfaceListener* listener)
	              {
		              listener->onResize(w, h);
	              });
}

void InputSource::notifyShow()
{
	std::for_each(_surfaceListeners.begin(),
	              _surfaceListeners.end(),
	              [](SurfaceListener* listener)
	              {
		              listener->onShow();
	              });
}

void InputSource::notifyHide()
{
	std::for_each(_surfaceListeners.begin(),
	              _surfaceListeners.end(),
	              [](SurfaceListener* listener)
	              {
		              listener->onHide();
	              });
}

void InputSource::notifyQuit()
{
	std::for_each(_surfaceListeners.begin(),
	              _surfaceListeners.end(),
	              [](SurfaceListener* listener)
	              {
		              listener->onQuit();
	              });
}

void InputSource::notifyKeyDown(key_type key)
{
	std::for_each(_keyListeners.begin(),
	              _keyListeners.end(),
	              [&](KeyListener* listener)
	              {
		              listener->onKeyDown(key);
	              });
}

void InputSource::notifyKeyUp(key_type key)
{
	std::for_each(_keyListeners.begin(),
	              _keyListeners.end(),
	              [&](KeyListener* listener)
	              {
		              listener->onKeyUp(key);
	              });
}

void InputSource::notifyPointerDown(pointer_id id,
                                    pointer_button button,
                                    int x,
                                    int y)
{
	std::for_each(_pointerListeners.begin(),
	              _pointerListeners.end(),
	              [&](PointerListener* listener)
	              {
		              listener->onPointerDown(id, button, x, y);
	              });
}

void InputSource::notifyPointerMove(pointer_id id,
                                    int dx,
                                    int dy)
{
	std::for_each(_pointerListeners.begin(),
	              _pointerListeners.end(),
	              [&](PointerListener* listener)
	              {
		              listener->onPointerMove(id, dx, dy);
	              });
}

void InputSource::notifyPointerDrag(pointer_id id,
                                    int dx,
                                    int dy)
{
	std::for_each(_pointerListeners.begin(),
	              _pointerListeners.end(),
	              [&](PointerListener* listener)
	              {
		              listener->onPointerDrag(id, dx, dy);
	              });
}

void InputSource::notifyPointerUp(pointer_id id,
                                  int x,
                                  int y)
{
	std::for_each(_pointerListeners.begin(),
	              _pointerListeners.end(),
	              [&](PointerListener* listener)
	              {
		              listener->onPointerUp(id, x, y);
	              });
}

void InputSource::notifyPointerZoom(int dz)
{
	std::for_each(_pointerListeners.begin(),
	              _pointerListeners.end(),
	              [&](PointerListener* listener)
	              {
		              listener->onPointerZoom(dz);
	              });
}

}

