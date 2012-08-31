/*
 * This file describes the smallest implemented public API for platform dependent time classes.
 *
 * To include platform specific header, use path "sys/Time.hpp".
 */

// For compatibility, use same macro-name.
#ifndef TIME_HPP_
#define TIME_HPP_

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
	 * @return the difference.
	 */
	TimeDuration operator-(const TimeDuration &other) const;

	/**
	 * Checks if time duration is positive.
	 *
	 * @return true if is positive (or zero), else false.
	 */
	bool isPositive() const;

	/**
	 * Checks if time duration is negative.
	 *
	 * @return true if is negative, else false.
	 */
	bool isNegative() const;

public:
	/**
	 * Gets the time duration between two time stamps.
	 *
	 * @param t1 first time stamp.
	 * @param t2 second time stamp.
	 * @return the time duration between the two time stamps.
	 */
	static TimeDuration between(const TimeStamp &t1,
	                            const TimeStamp &t2);
	/**
	 * Gets the time duration representing the specified milliseconds.
	 *
	 * @param ms the specified milliseconds.
	 * @return the time duration.
	 */
	static TimeDuration millis(unsigned long ms);
};

}

#endif /* TIME_HPP_ */
