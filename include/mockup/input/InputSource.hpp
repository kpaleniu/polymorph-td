/**
 * @file InputSource.hpp
 *
 */

#ifndef INPUTSOURCE_HPP_
#define INPUTSOURCE_HPP_

#include "unknown.hpp"

namespace input {

class SurfaceListener;
class KeyListener;
class PointerListener;

/**
 *
 */
class InputSource
{
public:
	bool handleInput();

	void registerSurfaceListener(SurfaceListener &);
	void unregisterSurfaceListener(SurfaceListener &);

	void registerKeyListener(KeyListener &);
	void unregisterKeyListener(KeyListener &);

	void registerSurfaceListener(PointerListener &);
	void unregisterSurfaceListener(PointerListener &);
};

}


#endif /* INPUTSOURCE_HPP_ */
