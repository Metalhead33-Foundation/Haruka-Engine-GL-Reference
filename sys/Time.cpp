#include "sys/Time.hpp"

void Time::sleep()
{
	SDL_Delay(milliseconds);
}
Time::Time()
	: milliseconds(0)
{
	;
}
Time::Time(Time& copyConstructor)
	: milliseconds(copyConstructor.milliseconds)
{
	;
}
Time::Time(uint64_t nmilliseconds)
	: milliseconds(nmilliseconds)
{
	;
}
Time::Time(double seconds)
	: milliseconds(uint64_t(seconds * 1000.00))
{
	;
}
uint64_t Time::getMilliseconds() const
{
	return milliseconds;
}
double Time::getSeconds() const
{
	return double(milliseconds) / 1000.00;
}
void Time::setMilliseconds(uint64_t milliseconds)
{
	this->milliseconds = milliseconds;
}
void Time::setSeconds(double seconds)
{
	this->milliseconds = uint64_t(seconds * 1000.00);
}

bool Time::operator==(Time& b) const
{
	return milliseconds == b.milliseconds;
}
bool Time::operator==(uint64_t& b) const
{
	return milliseconds == b;
}
bool Time::operator==(double& b) const
{
	return milliseconds == uint64_t(b * 1000.00);
}
bool Time::operator!=(Time& b) const
{
	return milliseconds != b.milliseconds;
}
bool Time::operator!=(uint64_t& b) const
{
	return milliseconds != b;
}
bool Time::operator!=(double& b) const
{
	return milliseconds != uint64_t(b * 1000.00);
}
bool Time::operator>(Time& b) const
{
	return milliseconds > b.milliseconds;
}
bool Time::operator>(uint64_t& b) const
{
	return milliseconds > b;
}
bool Time::operator>(double& b) const
{
	return milliseconds > uint64_t(b * 1000.00);
}
bool Time::operator<(Time& b) const
{
	return milliseconds < b.milliseconds;
}
bool Time::operator<(uint64_t& b) const
{
	return milliseconds < b;
}
bool Time::operator<(double& b) const
{
	return milliseconds < uint64_t(b * 1000.00);
}
bool Time::operator>=(Time& b) const
{
	return milliseconds >= b.milliseconds;
}
bool Time::operator>=(uint64_t& b) const
{
	return milliseconds >= b;
}
bool Time::operator>=(double& b) const
{
	return milliseconds >= uint64_t(b * 1000.00);
}
bool Time::operator<=(Time& b) const
{
	return milliseconds <= b.milliseconds;
}
bool Time::operator<=(uint64_t& b) const
{
	return milliseconds <= b;
}
bool Time::operator<=(double& b) const
{
	return milliseconds <= uint64_t(b * 1000.00);
}

void Time::operator=(Time& b)
{
	setMilliseconds(b.milliseconds);
}
void Time::operator=(uint64_t b)
{
	setMilliseconds(b);
}
void Time::operator=(double b)
{
	setSeconds(b);
}
void Time::operator+=(Time& b)
{
	milliseconds += b.milliseconds;
}
void Time::operator+=(uint64_t b)
{
	milliseconds += b;
}
void Time::operator+=(double b)
{
	milliseconds += uint64_t(b * 1000.00);
}
void Time::operator-=(Time& b)
{
	milliseconds -= b.milliseconds;
}
void Time::operator-=(uint64_t b)
{
	milliseconds -= b;
}
void Time::operator-=(double b)
{
	milliseconds -= uint64_t(b * 1000.00);
}
void Time::operator*=(Time& b)
{
	milliseconds *= b.milliseconds;
}
void Time::operator*=(uint64_t b)
{
	milliseconds *= b;
}
void Time::operator*=(double b)
{
	milliseconds *= uint64_t(b * 1000.00);
}
void Time::operator/=(Time& b)
{
	milliseconds /= b.milliseconds;
}
void Time::operator/=(uint64_t b)
{
	milliseconds /= b;
}
void Time::operator/=(double b)
{
	milliseconds /= uint64_t(b * 1000.00);
}
void Time::operator%=(Time& b)
{
	milliseconds %= b.milliseconds;
}
void Time::operator%=(uint64_t b)
{
	milliseconds %= b;
}
void Time::operator%=(double b)
{
	milliseconds %= uint64_t(b * 1000.00);
}
Time Time::operator+(Time& b)
{
	Time tmp(milliseconds);
	tmp += b;
	return tmp;
}
Time Time::operator+(uint64_t b)
{
	Time tmp(milliseconds);
	tmp += b;
	return tmp;
}
Time Time::operator+(double b)
{
	Time tmp(milliseconds);
	tmp += b;
	return tmp;
}
Time Time::operator-(Time& b)
{
	Time tmp(milliseconds);
	tmp -= b;
	return tmp;
}
Time Time::operator-(uint64_t b)
{
	Time tmp(milliseconds);
	tmp -= b;
	return tmp;
}
Time Time::operator-(double b)
{
	Time tmp(milliseconds);
	tmp -= b;
	return tmp;
}
Time Time::operator*(Time& b)
{
	Time tmp(milliseconds);
	tmp *= b;
	return tmp;
}
Time Time::operator*(uint64_t b)
{
	Time tmp(milliseconds);
	tmp *= b;
	return tmp;
}
Time Time::operator*(double b)
{
	Time tmp(milliseconds);
	tmp *= b;
	return tmp;
}
Time Time::operator/(Time& b)
{
	Time tmp(milliseconds);
	tmp /= b;
	return tmp;
}
Time Time::operator/(uint64_t b)
{
	Time tmp(milliseconds);
	tmp /= b;
	return tmp;
}
Time Time::operator/(double b)
{
	Time tmp(milliseconds);
	tmp /= b;
	return tmp;
}
Time Time::operator%(Time& b)
{
	Time tmp(milliseconds);
	tmp %= b;
	return tmp;
}
Time Time::operator%(uint64_t b)
{
	Time tmp(milliseconds);
	tmp %= b;
	return tmp;
}
Time Time::operator%(double b)
{
	Time tmp(milliseconds);
	tmp %= b;
	return tmp;
}
