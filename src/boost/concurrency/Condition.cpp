/**
 * @file Condition.cpp
 *
 */


#include "concurrency/Condition.hpp"

namespace concurrency {

Condition::Condition()
:	_mutex(),
 	_cond()
{
}

void Condition::notifyAll()
{
	_cond.notify_all();
}

Mutex &Condition::mutex()
{
	return _mutex;
}

}
