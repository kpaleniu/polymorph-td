#ifndef STD_TIME_HPP_
#define STD_TIME_HPP_

#include <chrono>

class TimeStamp
{
public:

	static TimeStamp now();

public:
	std::chrono::system_clock::time_point _timeStamp;

private:
	TimeStamp(const std::chrono::system_clock::time_point& timeStamp);
};

class TimeDuration
{
public:

	/**
	 * An explicitly 64-bit type for millisecond TimeDurations.
	 */
	typedef int64_t tick_type;

	TimeDuration operator-(const TimeDuration& other) const;

	bool operator==(const TimeDuration& other) const;
	bool operator!=(const TimeDuration& other) const;
	bool operator<(const TimeDuration& other) const;
	bool operator>(const TimeDuration& other) const;
	bool operator<=(const TimeDuration& other) const;
	bool operator>=(const TimeDuration& other) const;

	tick_type toMillis() const;

public:

	static TimeDuration between(const TimeStamp& t1,
	                            const TimeStamp& t2);


	static TimeDuration millis(tick_type ms);

public:
	std::chrono::milliseconds timeDuration;

private:
	TimeDuration(const std::chrono::milliseconds& _timeDuration);

};

#endif
