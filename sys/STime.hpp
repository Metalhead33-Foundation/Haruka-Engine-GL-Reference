#pragma once
#include "../abstract/Global.hpp"
#include <SDL2/SDL_timer.h>

DEFINE_CLASS(STime)

class STime
{
private:
	int64_t milliseconds;
public:
	STime();
	STime(const STime& copyConstructor);
	STime(int64_t nmilliseconds);

	static STime asMilliseconds(int64_t milliseconds);
	static STime asSeconds(double seconds);
	static STime asMinutes(double minutes);
	static STime asHours(double hours);
	static STime asDays(double days);

	int64_t getMilliseconds() const;
	double getSeconds() const;
	void setMilliseconds(int64_t milliseconds);
	void setSeconds(double seconds);
	void sleep();

	bool operator==(const STime& b) const;
	bool operator==(int64_t& b) const;
	bool operator==(double& b) const;
	bool operator!=(const STime& b) const;
	bool operator!=(int64_t& b) const;
	bool operator!=(double& b) const;
	bool operator>(const STime& b) const;
	bool operator>(int64_t& b) const;
	bool operator>(double& b) const;
	bool operator<(const STime& b) const;
	bool operator<(int64_t& b) const;
	bool operator<(double& b) const;
	bool operator>=(const STime& b) const;
	bool operator>=(int64_t& b) const;
	bool operator>=(double& b) const;
	bool operator<=(const STime& b) const;
	bool operator<=(int64_t& b) const;
	bool operator<=(double& b) const;

	STime& operator=(const STime& b);
	STime& operator=(int64_t b);
	STime& operator=(double b);
	STime& operator+=(const STime& b);
	STime& operator+=(int64_t b);
	STime& operator+=(double b);
	STime& operator-=(const STime& b);
	STime& operator-=(int64_t b);
	STime& operator-=(double b);
	STime& operator*=(const STime& b);
	STime& operator*=(int64_t b);
	STime& operator*=(double b);
	STime& operator/=(const STime& b);
	STime& operator/=(int64_t b);
	STime& operator/=(double b);
	STime& operator%=(const STime& b);
	STime& operator%=(int64_t b);
	STime& operator%=(double b);

	STime operator+(const STime& b) const;
	STime operator+(int64_t b) const;
	STime operator+(double b) const;
	STime operator-(const STime& b) const;
	STime operator-(int64_t b) const;
	STime operator-(double b) const;
	STime operator*(const STime& b) const;
	STime operator*(int64_t b) const;
	STime operator*(double b) const;
	STime operator/(const STime& b) const;
	STime operator/(int64_t b) const;
	STime operator/(double b) const;
	STime operator%(const STime& b) const;
	STime operator%(int64_t b) const;
	STime operator%(double b) const;

	static const STime oneSecond;
	static const STime oneMinute;
	static const STime oneHour;
	static const STime oneDay;
};
inline const STime operator "" _ms(unsigned long long a)
{
	return STime(int64_t(a));
}
inline const STime operator "" _s(long double a)
{
	return STime(double(a));
}
inline const STime operator "" _m(long double a)
{
	return STime(double(a * 60.00));
}
inline const STime operator "" _h(long double a)
{
	return STime(double(a * 3600.00));
}
inline STime operator "" _d(long double a)
{
	return STime(double(a * 86400.00));
}
