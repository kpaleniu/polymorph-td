/**
 * @file ptr.hpp
 *
 */

#include <boost/shared_ptr.hpp>

template <typename T>
struct ptr
{
	typedef boost::shared_ptr<T> shared;
};

