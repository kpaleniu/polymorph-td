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
	virtual void onDestroy() = 0;
};

}


#endif /* SURFACELISTENER_HPP_ */
