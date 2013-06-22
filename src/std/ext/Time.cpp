/**
 * @file Time.cpp
 *
 */

#include "Time.hpp"

// TimeStamp implementation

TimeStamp::TimeStamp(const std::chrono::system_clock::time_point& timeStamp)
:	_timeStamp(timeStamp)
{
}

TimeStamp TimeStamp::now()
{
	return TimeStamp(std::chrono::system_clock::now());
}

// TimeDuration implementation

TimeDuration::TimeDuration(const std::chrono::milliseconds& _timeDuration)
		: timeDuration(_timeDuration)
{
	//
}

TimeDuration TimeDuration::operator-(const TimeDuration &other) const
{
	return TimeDuration(timeDuration
	                    - other.timeDuration);
}

bool TimeDuration::operator==(const TimeDuration& other) const
{
	return timeDuration == other.timeDuration;
}

bool TimeDuration::operator!=(const TimeDuration& other) const
{
	return timeDuration != other.timeDuration;
}

bool TimeDuration::operator<(const TimeDuration& other) const
{
	return timeDuration < other.timeDuration;
}

bool TimeDuration::operator>(const TimeDuration& other) const
{
	return timeDuration > other.timeDuration;
}

bool TimeDuration::operator<=(const TimeDuration& other) const
{
	return timeDuration <= other.timeDuration;
}

bool TimeDuration::operator>=(const TimeDuration& other) const
{
	return timeDuration >= other.timeDuration;
}

TimeDuration::tick_type TimeDuration::toMillis() const
{
	return timeDuration.count();
}

TimeDuration TimeDuration::between(const TimeStamp &t1,
                                   const TimeStamp &t2)
{
	return TimeDuration(std::chrono::duration_cast<std::chrono::milliseconds>(t2._timeStamp
	                    - t1._timeStamp));
}

TimeDuration TimeDuration::millis(tick_type ms)
{
	return TimeDuration(std::chrono::milliseconds(ms));
}


