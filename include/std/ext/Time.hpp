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

	tick_type toMillis() const;
	float toSecs() const;

public:

	static TimeDuration between(const TimeStamp& t1,
	                            const TimeStamp& t2);

	static TimeDuration millis(tick_type ms);

public:
	// May only be used inside ext-api std.

	std::chrono::milliseconds _std__timeDuration;
	TimeDuration(const std::chrono::milliseconds& _timeDuration);
};

TimeDuration operator-(const TimeDuration& t1, const TimeDuration& t2);
TimeDuration operator+(const TimeDuration& t1, const TimeDuration& t2);

TimeDuration& operator-=(TimeDuration& t1, const TimeDuration& t2);
TimeDuration& operator+=(TimeDuration& t1, const TimeDuration& t2);

bool operator==(const TimeDuration& t1, const TimeDuration& t2);
bool operator!=(const TimeDuration& t1, const TimeDuration& t2);
bool operator<(const TimeDuration& t1, const TimeDuration& t2);
bool operator>(const TimeDuration& t1, const TimeDuration& t2);
bool operator<=(const TimeDuration& t1, const TimeDuration& t2);
bool operator>=(const TimeDuration& t1, const TimeDuration& t2);

#endif
