/**
 * @file Time.cpp
 *
 */

#include "Time.hpp"

// TimeStamp implementation

TimeStamp::TimeStamp(const boost::posix_time::ptime &timeStamp)
		: _timeStamp(timeStamp)
{
	//
}

TimeStamp TimeStamp::now()
{
	return TimeStamp(boost::posix_time::microsec_clock::local_time());
}

// TimeDuration implementation

TimeDuration::TimeDuration(const boost::posix_time::time_duration &_timeDuration)
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

bool TimeDuration::isPositive() const
{
	return !timeDuration.is_negative();
}

bool TimeDuration::isNegative() const
{
	return timeDuration.is_negative();
}

TimeDuration::tick_type TimeDuration::toMillis() const
{
	return timeDuration.total_milliseconds();
}

TimeDuration TimeDuration::between(const TimeStamp &t1,
                                   const TimeStamp &t2)
{
	return TimeDuration(t2._timeStamp
	                    - t1._timeStamp);
}

TimeDuration TimeDuration::millis(tick_type ms)
{
	return TimeDuration(boost::posix_time::millisec(ms));
}


