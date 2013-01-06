/**
 * @file InputSource.cpp
 *
 */

#include "input/InputSource.hpp"

#include <Assert.hpp>

#include <algorithm>

namespace input {

InputSource::InputSource()
:	_surfaceListener(nullptr),
 	_keyListener(nullptr),
 	_pointerListener(nullptr)
{
}

InputSource::~InputSource()
{
}

void InputSource::setSurfaceListener(SurfaceListener* listener)
{
	_surfaceListener = listener;
}

void InputSource::setKeyListener(KeyListener* listener)
{
	_keyListener = listener;
}

void InputSource::setPointerListener(PointerListener* listener)
{
	_pointerListener = listener;
}

void InputSource::notifyResize(int w, int h)
{
	if (_surfaceListener != nullptr)
		_surfaceListener->onResize(w, h);
}

void InputSource::notifyShow()
{
	if (_surfaceListener != nullptr)
		_surfaceListener->onShow();
}

void InputSource::notifyHide()
{
	if (_surfaceListener != nullptr)
		_surfaceListener->onHide();
}

void InputSource::notifyQuit()
{
	if (_surfaceListener != nullptr)
		_surfaceListener->onQuit();
}

void InputSource::notifyKeyDown(key_type key)
{
	if (_keyListener != nullptr)
		_keyListener->onKeyDown(key);
}

void InputSource::notifyKeyUp(key_type key)
{
	if (_keyListener != nullptr)
		_keyListener->onKeyUp(key);
}

void InputSource::notifyPointerDown(pointer_id id,
                                    pointer_button button,
                                    long x,
                                    long y)
{
	if (_pointerListener != nullptr)
		_pointerListener->onPointerDown(id, button, x, y);
}

void InputSource::notifyPointerMove(pointer_id id,
                                    int dx,
                                    int dy)
{
	if (_pointerListener != nullptr)
		_pointerListener->onPointerMove(id, dx, dy);
}

void InputSource::notifyPointerDrag(pointer_id id,
                                    int dx,
                                    int dy)
{
	if (_pointerListener != nullptr)
		_pointerListener->onPointerDrag(id, dx, dy);
}

void InputSource::notifyPointerUp(pointer_id id,
                                  pointer_button button,
                                  long x,
                                  long y)
{
	if (_pointerListener != nullptr)
		_pointerListener->onPointerUp(id, button, x, y);
}

void InputSource::notifyPointerZoom(int dz)
{
	if (_pointerListener != nullptr)
		_pointerListener->onPointerZoom(dz);
}

}

