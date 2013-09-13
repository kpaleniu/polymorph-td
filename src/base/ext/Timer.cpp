#include "Timer.hpp"

#include "Assert.hpp"

Timer::Timer(TimeDuration period, std::function<void ()> && action)
:	_period(period),
	_counter(TimeDuration::millis(0)),
	_action(std::move(action))
{
	ASSERT(_period > TimeDuration::millis(0),
		   "Timer's period must be higher than 0");
}

void Timer::update(TimeDuration dt)
{
	_counter += dt;

	if (_counter >= _period)
	{
		_counter -= _period;
		
		if (_action)
			_action();
	}
}

std::function<void ()>& Timer::action()
{
	return _action;
}