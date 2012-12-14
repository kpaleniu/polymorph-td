/**
 * @file PrivateHandle.hpp
 *
 * Defines a wrapper that limits the visibility of the object it wraps.
 *
 * NOTE, this requires delegating constructors.
 */

#ifndef PRIVATEHANDLE_HPP_
#define PRIVATEHANDLE_HPP_

#include "NonCopyable.hpp"

/**
 * Base class for the wrapper.
 */
template <typename T>
class PrivateHandle
{
protected:
	PrivateHandle()				: _val() 	{}
	PrivateHandle(const T& val) : _val(val)	{}

	PrivateHandle& operator=(const T& val)
	{ _val = val; return *this; }

	operator T()
	{ return _val; }

	T _val;
};


// Should mostly be used with typedef.
// Parameter "friendObject" should be in format "class MyClass" for classes.
#define NEW_PRIVATE_HANDLE_T(clazz, friendObject) \
class : public PrivateHandle<clazz> \
{ using PrivateHandle<clazz>::PrivateHandle; \
  friend friendObject; }

#endif /* PRIVATEHANDLE_HPP_ */
