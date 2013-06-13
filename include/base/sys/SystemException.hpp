/**
 * @file SystemException.hpp
 *
 */

#ifndef SYSTEM_EXCEPTION_HPP_
#define SYSTEM_EXCEPTION_HPP_

#include "Exception.hpp"

namespace polymorph { namespace sys {

PM_MAKE_EXCEPTION_CLASS(SystemException, Exception);

} }	// namespace sys

#endif /* SYSTEM_EXCEPTION_HPP_ */
