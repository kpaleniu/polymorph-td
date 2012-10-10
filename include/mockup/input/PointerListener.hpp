/**
 * @file PointerListener.hpp
 *
 */

#ifndef POINTERLISTENER_HPP_
#define POINTERLISTENER_HPP_

namespace input {

typedef platform_type pointer_button;

class PointerListener
{
public:
	virtual ~PointerListener() {}

	virtual void onPointerDown(pointer_button button, int x, int y) = 0;
	virtual void onPointerMove(int dx, int dy) = 0;
	virtual void onPointerDrag(int dx, int dy) = 0;
	virtual void onPointerUp(int x, int y) = 0;
	virtual void onPointerZoom(int dz) = 0;
};

class PointerEventSubscription
{
public:
	SurfaceSubscription(InputSource &inputSource, PointerListener &pointerListener)
	: _inputSource(inputSource), _pointerListener(pointerListener)
	{
		_inputSource.registerPointerListener(_pointerListener);
	}
	~SurfaceSubscription()
	{
		_inputSource.unregisterPointerListener(_pointerListener);
	}

private:
	InputSource &_inputSource;
	PointerListener &_keyListener;
};


}


#endif /* POINTERLISTENER_HPP_ */
