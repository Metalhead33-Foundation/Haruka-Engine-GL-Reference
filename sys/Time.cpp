#include "sys/Time.hpp"

const Time Time::oneSecond(1.00_s);
const Time Time::oneMinute(1.00_m);
const Time Time::oneHour(1.00_h);
const Time Time::oneDay(1.00_d);
void Time::sleep()
{
	SDL_Delay(milliseconds);
}
Time::Time()
	: milliseconds(0)
{
	;
}
Time::Time(const Time& copyConstructor)
	: milliseconds(copyConstructor.milliseconds)
{
	;
}
Time::Time(int64_t nmilliseconds)
	: milliseconds(nmilliseconds)
{
	;
}
Time Time::asMilliseconds(int64_t milliseconds)
{
	return Time(milliseconds);
}
Time Time::asSeconds(double seconds)
{
	return Time(oneSecond * seconds);
}
Time Time::asMinutes(double minutes)
{
	return Time(oneMinute * minutes);
}
Time Time::asHours(double hours)
{
	return Time(oneHour * hours);
}
Time Time::asDays(double days)
{
	return Time(oneDay * days);
}
int64_t Time::getMilliseconds() const
{
	return milliseconds;
}
double Time::getSeconds() const
{
	return double(milliseconds) / 1000.00;
}
void Time::setMilliseconds(int64_t milliseconds)
{
	this->milliseconds = milliseconds;
}
void Time::setSeconds(double seconds)
{
	this->milliseconds = int64_t(seconds * 1000.00);
}

bool Time::operator==(const Time& b) const
{
	return milliseconds == b.milliseconds;
}
bool Time::operator==(int64_t& b) const
{
	return milliseconds == b;
}
bool Time::operator==(double& b) const
{
	return milliseconds == int64_t(b * 1000.00);
}
bool Time::operator!=(const Time& b) const
{
	return milliseconds != b.milliseconds;
}
bool Time::operator!=(int64_t& b) const
{
	return milliseconds != b;
}
bool Time::operator!=(double& b) const
{
	return milliseconds != int64_t(b * 1000.00);
}
bool Time::operator>(const Time& b) const
{
	return milliseconds > b.milliseconds;
}
bool Time::operator>(int64_t& b) const
{
	return milliseconds > b;
}
bool Time::operator>(double& b) const
{
	return milliseconds > int64_t(b * 1000.00);
}
bool Time::operator<(const Time& b) const
{
	return milliseconds < b.milliseconds;
}
bool Time::operator<(int64_t& b) const
{
	return milliseconds < b;
}
bool Time::operator<(double& b) const
{
	return milliseconds < int64_t(b * 1000.00);
}
bool Time::operator>=(const Time& b) const
{
	return milliseconds >= b.milliseconds;
}
bool Time::operator>=(int64_t& b) const
{
	return milliseconds >= b;
}
bool Time::operator>=(double& b) const
{
	return milliseconds >= int64_t(b * 1000.00);
}
bool Time::operator<=(const Time& b) const
{
	return milliseconds <= b.milliseconds;
}
bool Time::operator<=(int64_t& b) const
{
	return milliseconds <= b;
}
bool Time::operator<=(double& b) const
{
	return milliseconds <= int64_t(b * 1000.00);
}

Time& Time::operator=(const Time& b)
{
	setMilliseconds(b.milliseconds);
	return *this;
}
Time& Time::operator=(int64_t b)
{
	setMilliseconds(b);
	return *this;
}
Time& Time::operator=(double b)
{
	setSeconds(b);
	return *this;
}
Time& Time::operator+=(const Time& b)
{
	milliseconds += b.milliseconds;
	return *this;
}
Time& Time::operator+=(int64_t b)
{
	milliseconds += b;
	return *this;
}
Time& Time::operator+=(double b)
{
	milliseconds += int64_t(b * 1000.00);
	return *this;
}
Time& Time::operator-=(const Time& b)
{
	milliseconds -= b.milliseconds;
	return *this;
}
Time& Time::operator-=(int64_t b)
{
	milliseconds -= b;
	return *this;
}
Time& Time::operator-=(double b)
{
	milliseconds -= int64_t(b * 1000.00);
	return *this;
}
Time& Time::operator*=(const Time& b)
{
	milliseconds *= b.milliseconds;
	return *this;
}
Time& Time::operator*=(int64_t b)
{
	milliseconds *= b;
	return *this;
}
Time& Time::operator*=(double b)
{
	milliseconds *= int64_t(b);
	return *this;
}
Time& Time::operator/=(const Time& b)
{
	milliseconds /= b.milliseconds;
	return *this;
}
Time& Time::operator/=(int64_t b)
{
	milliseconds /= b;
	return *this;
}
Time& Time::operator/=(double b)
{
	milliseconds /= int64_t(b);
	return *this;
}
Time& Time::operator%=(const Time& b)
{
	milliseconds %= b.milliseconds;
	return *this;
}
Time& Time::operator%=(int64_t b)
{
	milliseconds %= b;
	return *this;
}
Time& Time::operator%=(double b)
{
	milliseconds %= int64_t(b * 1000.00);
	return *this;
}
Time Time::operator+(const Time& b) const
{
	Time tmp(milliseconds);
	tmp += b;
	return tmp;
}
Time Time::operator+(int64_t b) const
{
	Time tmp(milliseconds);
	tmp += b;
	return tmp;
}
Time Time::operator+(double b) const
{
	Time tmp(milliseconds);
	tmp += b;
	return tmp;
}
Time Time::operator-(const Time& b) const
{
	Time tmp(milliseconds);
	tmp -= b;
	return tmp;
}
Time Time::operator-(int64_t b) const
{
	Time tmp(milliseconds);
	tmp -= b;
	return tmp;
}
Time Time::operator-(double b) const
{
	Time tmp(milliseconds);
	tmp -= b;
	return tmp;
}
Time Time::operator*(const Time& b) const
{
	Time tmp(milliseconds);
	tmp *= b;
	return tmp;
}
Time Time::operator*(int64_t b) const
{
	Time tmp(milliseconds);
	tmp *= b;
	return tmp;
}
Time Time::operator*(double b) const
{
	Time tmp(milliseconds);
	tmp *= b;
	return tmp;
}
Time Time::operator/(const Time& b) const
{
	Time tmp(milliseconds);
	tmp /= b;
	return tmp;
}
Time Time::operator/(int64_t b) const
{
	Time tmp(milliseconds);
	tmp /= b;
	return tmp;
}
Time Time::operator/(double b) const
{
	Time tmp(milliseconds);
	tmp /= b;
	return tmp;
}
Time Time::operator%(const Time& b) const
{
	Time tmp(milliseconds);
	tmp %= b;
	return tmp;
}
Time Time::operator%(int64_t b) const
{
	Time tmp(milliseconds);
	tmp %= b;
	return tmp;
}
Time Time::operator%(double b) const
{
	Time tmp(milliseconds);
	tmp %= b;
	return tmp;
}
