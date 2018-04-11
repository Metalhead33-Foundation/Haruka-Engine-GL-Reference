#ifndef TIME_HPP
#define TIME_HPP
#include "../abstract/Global.hpp"
#include <SDL2/SDL_timer.h>

DEFINE_CLASS(Time)

class Time
{
private:
	int64_t milliseconds;
public:
	Time();
	Time(const Time& copyConstructor);
	Time(int64_t nmilliseconds);

	static Time asMilliseconds(int64_t milliseconds);
	static Time asSeconds(double seconds);
	static Time asMinutes(double minutes);
	static Time asHours(double hours);
	static Time asDays(double days);

	int64_t getMilliseconds() const;
	double getSeconds() const;
	void setMilliseconds(int64_t milliseconds);
	void setSeconds(double seconds);
	void sleep();

	bool operator==(const Time& b) const;
	bool operator==(int64_t& b) const;
	bool operator==(double& b) const;
	bool operator!=(const Time& b) const;
	bool operator!=(int64_t& b) const;
	bool operator!=(double& b) const;
	bool operator>(const Time& b) const;
	bool operator>(int64_t& b) const;
	bool operator>(double& b) const;
	bool operator<(const Time& b) const;
	bool operator<(int64_t& b) const;
	bool operator<(double& b) const;
	bool operator>=(const Time& b) const;
	bool operator>=(int64_t& b) const;
	bool operator>=(double& b) const;
	bool operator<=(const Time& b) const;
	bool operator<=(int64_t& b) const;
	bool operator<=(double& b) const;

	Time& operator=(const Time& b);
	Time& operator=(int64_t b);
	Time& operator=(double b);
	Time& operator+=(const Time& b);
	Time& operator+=(int64_t b);
	Time& operator+=(double b);
	Time& operator-=(const Time& b);
	Time& operator-=(int64_t b);
	Time& operator-=(double b);
	Time& operator*=(const Time& b);
	Time& operator*=(int64_t b);
	Time& operator*=(double b);
	Time& operator/=(const Time& b);
	Time& operator/=(int64_t b);
	Time& operator/=(double b);
	Time& operator%=(const Time& b);
	Time& operator%=(int64_t b);
	Time& operator%=(double b);

	Time operator+(const Time& b) const;
	Time operator+(int64_t b) const;
	Time operator+(double b) const;
	Time operator-(const Time& b) const;
	Time operator-(int64_t b) const;
	Time operator-(double b) const;
	Time operator*(const Time& b) const;
	Time operator*(int64_t b) const;
	Time operator*(double b) const;
	Time operator/(const Time& b) const;
	Time operator/(int64_t b) const;
	Time operator/(double b) const;
	Time operator%(const Time& b) const;
	Time operator%(int64_t b) const;
	Time operator%(double b) const;

	static const Time oneSecond;
	static const Time oneMinute;
	static const Time oneHour;
	static const Time oneDay;
};
inline const Time operator "" _ms(unsigned long long a)
{
	return Time(int64_t(a));
}
inline const Time operator "" _s(long double a)
{
	return Time(double(a));
}
inline const Time operator "" _m(long double a)
{
	return Time(double(a * 60.00));
}
inline const Time operator "" _h(long double a)
{
	return Time(double(a * 3600.00));
}
inline Time operator "" _d(long double a)
{
	return Time(double(a * 86400.00));
}

#endif // TIME_HPP
