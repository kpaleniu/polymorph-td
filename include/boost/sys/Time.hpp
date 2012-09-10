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
	static TimeStamp now();

public:
	boost::posix_time::ptime _timeStamp;

private:
	TimeStamp(const boost::posix_time::ptime &timeStamp);
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
	TimeDuration operator-(const TimeDuration &other) const;

	/**
	 * Checks if time duration is positive.
	 */
	bool isPositive() const;

	/**
	 * Checks if time duration is negative.
	 */
	bool isNegative() const;

	long toMillis() const;

public:
	/**
	 * Gets the time duration between two time stamps.
	 *
	 * @param t1 first time stamp.
	 * @param t2 second time stamp.
	 */
	static TimeDuration between(const TimeStamp &t1,
	                            const TimeStamp &t2);

	/**
	 * Gets the time duration representing the specified milliseconds.
	 *
	 * @param ms the specified milliseconds.
	 */
	static TimeDuration millis(long ms);

public:
	boost::posix_time::time_duration timeDuration;

private:
	TimeDuration(const boost::posix_time::time_duration &_timeDuration);

};

}

#endif /* TIME_HPP_ */
