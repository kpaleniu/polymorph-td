/**
 * @file KeyListener.hpp
 *
 */

#ifndef KEYLISTENER_HPP_
#define KEYLISTENER_HPP_

#include "input/InputSource.hpp"

namespace input {

typedef platform_type key_type; // Should probably not be "that" platform specific.

class KeyListener
{
public:
	virtual ~KeyListener() {}

	virtual void onKeyDown(key_type key) = 0;
	virtual void onKeyUp(key_type key) = 0;
};

class KeyEventSubscription
{
public:
	SurfaceSubscription(InputSource &inputSource, KeyListener &keyListener)
	: _inputSource(inputSource), _keyListener(keyListener)
	{
		_inputSource.registerKeyListener(_keyListener);
	}

	~SurfaceSubscription()
	{
		_inputSource.unregisterKeyListener(_keyListener);
	}

private:
	InputSource &_inputSource;
	KeyListener &_keyListener;
};

}


#endif /* KEYLISTENER_HPP_ */
