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

SurfaceEventSubscription InputSource::surfaceSubscription(SurfaceListener& listener)
{
	return SurfaceEventSubscription(
	[&]
	{
		ASSERT(_surfaceListener == nullptr, "Overwriting previous subscription");
		_surfaceListener = &listener;
	},
	[&]
	{
		ASSERT(_surfaceListener != nullptr, "Removing non-existing subscription");
		_surfaceListener = nullptr;
	});
}


KeyEventSubscription InputSource::keySubscription(KeyListener& listener)
{
	return KeyEventSubscription(
	[&]
	{
		ASSERT(_keyListener == nullptr, "Overwriting previous subscription");
		_keyListener = &listener;
	},
	[&]
	{
		ASSERT(_keyListener != nullptr, "Removing non-existing subscription");
		_keyListener = nullptr;
	});
}

PointerEventSubscription InputSource::pointerSubscription(PointerListener& listener)
{
	return PointerEventSubscription(
	[&]
	{
		ASSERT(_pointerListener == nullptr, "Overwriting previous subscription");
		_pointerListener = &listener;
	},
	[&]
	{
		ASSERT(_pointerListener != nullptr, "Removing non-existing subscription");
		_pointerListener = nullptr;
	});
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
                                    int x,
                                    int y)
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
                                  int x,
                                  int y)
{
	if (_pointerListener != nullptr)
		_pointerListener->onPointerUp(id, x, y);
}

void InputSource::notifyPointerZoom(int dz)
{
	if (_pointerListener != nullptr)
		_pointerListener->onPointerZoom(dz);
}

}

