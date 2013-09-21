/**
 * @file KeyListener.hpp
 *
 */

#ifndef KEYLISTENER_HPP_
#define KEYLISTENER_HPP_

namespace polymorph { namespace input {

typedef int key_type; // Should probably not be "that" platform specific.

class KeyListener
{
public:
	virtual ~KeyListener() {}

	virtual void onKeyDown(key_type key) = 0;
	virtual void onKeyUp(key_type key) = 0;
};

} }


#endif /* KEYLISTENER_HPP_ */
