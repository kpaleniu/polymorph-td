#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "Time.hpp"
#include "NonCopyable.hpp"

#include <functional>

class Timer : NonCopyable
{
public:
	Timer(TimeDuration period, 
		  std::function<void ()>&& action = std::function<void()>());

	Timer(Timer&& other);

	void update(TimeDuration dt);

	std::function<void ()>& action();

private:
	const TimeDuration _period;
	TimeDuration _counter;
	std::function<void ()> _action;
};

#endif