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
:	_std__timeDuration(_timeDuration)
{
	//
}

TimeDuration::tick_type TimeDuration::toMillis() const
{
	return _std__timeDuration.count();
}

float TimeDuration::toSecs() const
{
	return float(_std__timeDuration.count()) / 1000.0f;
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


TimeDuration operator-(const TimeDuration& t1, const TimeDuration& t2)
{
	return TimeDuration(t1._std__timeDuration - t2._std__timeDuration);
}

TimeDuration operator+(const TimeDuration& t1, const TimeDuration& t2)
{
	return TimeDuration(t1._std__timeDuration + t2._std__timeDuration);
}

TimeDuration& operator-=(TimeDuration& t1, const TimeDuration& t2)
{
	t1._std__timeDuration -= t2._std__timeDuration;
	return t1;
}

TimeDuration& operator+=(TimeDuration& t1, const TimeDuration& t2)
{
	t1._std__timeDuration += t2._std__timeDuration;
	return t1;
}

bool operator==(const TimeDuration& t1, const TimeDuration& t2)
{
	return t1._std__timeDuration == t2._std__timeDuration;
}

bool operator!=(const TimeDuration& t1, const TimeDuration& t2)
{
	return t1._std__timeDuration != t2._std__timeDuration;
}

bool operator<(const TimeDuration& t1, const TimeDuration& t2)
{
	return t1._std__timeDuration < t2._std__timeDuration;
}

bool operator>(const TimeDuration& t1, const TimeDuration& t2)
{
	return t1._std__timeDuration > t2._std__timeDuration;
}

bool operator<=(const TimeDuration& t1, const TimeDuration& t2)
{
	return t1._std__timeDuration <= t2._std__timeDuration;
}

bool operator>=(const TimeDuration& t1, const TimeDuration& t2)
{
	return t1._std__timeDuration >= t2._std__timeDuration;
}