/*
 * @file Time.hpp
 *
 *
 */

#ifndef TIME_HPP_
#define TIME_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>

namespace sys {

/**
 * Class representing a point in time.
 */
class TimeStamp
{
public:
	/**
	 * Gets the current point in time.
	 */
	static TimeStamp now()
	{
		return TimeStamp(boost::posix_time::microsec_clock::local_time());
	}

public:
	boost::posix_time::ptime _timeStamp;

private:
	TimeStamp(const boost::posix_time::ptime &timeStamp)
			: _timeStamp(timeStamp)
	{
		//
	}
};

/**
 * Class encapsulating a time period.
 */
class TimeDuration
{
public:

	/**
	 * Gets the difference between another time durations.
	 *
	 * @param other the other time duration.
	 */
	TimeDuration operator-(const TimeDuration &other) const
	{
		return TimeDuration(timeDuration
		                    - other.timeDuration);
	}

	/**
	 * Checks if time duration is positive.
	 */
	bool isPositive() const
	{
		return !timeDuration.is_negative();
	}

	/**
	 * Checks if time duration is negative.
	 */
	bool isNegative() const
	{
		return timeDuration.is_negative();
	}

	long toMillis() const
	{
		return timeDuration.total_milliseconds();
	}

public:
	/**
	 * Gets the time duration between two time stamps.
	 *
	 * @param t1 first time stamp.
	 * @param t2 second time stamp.
	 */
	static TimeDuration between(const TimeStamp &t1,
	                            const TimeStamp &t2)
	{
		return TimeDuration(t2._timeStamp
		                    - t1._timeStamp);
	}

	/**
	 * Gets the time duration representing the specified milliseconds.
	 *
	 * @param ms the specified milliseconds.
	 */
	static TimeDuration millis(long ms)
	{
		return TimeDuration(boost::posix_time::millisec(ms));
	}

public:
	boost::posix_time::time_duration timeDuration;

private:
	TimeDuration(const boost::posix_time::time_duration &_timeDuration)
			: timeDuration(_timeDuration)
	{
		//
	}

};

}

#endif /* TIME_HPP_ */
