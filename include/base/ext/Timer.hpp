#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "Time.hpp"

#include <functional>

class Timer
{
public:
	Timer(TimeDuration period, 
		  std::function<void ()>&& action = std::function<void()>());

	void update(TimeDuration dt);

	std::function<void ()>& action();

private:
	const TimeDuration _period;
	TimeDuration _counter;
	std::function<void ()> _action;
};

#endif