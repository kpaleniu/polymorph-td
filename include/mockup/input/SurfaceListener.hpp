/**
 * @file SurfaceListener.hpp
 *
 */

#ifndef SURFACELISTENER_HPP_
#define SURFACELISTENER_HPP_

namespace input {

class SurfaceListener
{
public:
	virtual ~SurfaceListener() {}

	virtual void onResize(int w, int h) = 0;
	virtual void onShow() = 0;
	virtual void onHide() = 0;
};

class SurfaceEventSubscription
{
public:
	SurfaceSubscription(InputSource &inputSource, SurfaceListener &surfaceListener)
	: _inputSource(inputSource), _surfaceListener(surfaceListener)
	{
		_inputSource.registerSurfaceListener(_surfaceListener);
	}

	~SurfaceSubscription()
	{
		_inputSource.unregisterSurfaceListener(_surfaceListener);
	}

private:
	InputSource &_inputSource;
	SurfaceListener &_surfaceListener;
};

}


#endif /* SURFACELISTENER_HPP_ */
