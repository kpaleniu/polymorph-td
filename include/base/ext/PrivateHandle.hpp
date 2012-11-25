/**
 * @file PrivateHandle.hpp
 *
 */

#ifndef PRIVATEHANDLE_HPP_
#define PRIVATEHANDLE_HPP_

#define PRIVATE_HANDLE_T(clazz, friendClazz) \
	struct {private: clazz value; friend class friendClazz;}

#endif /* PRIVATEHANDLE_HPP_ */
