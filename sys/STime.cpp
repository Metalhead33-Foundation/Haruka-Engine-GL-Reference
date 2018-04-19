#include "sys/STime.hpp"

const STime STime::oneSecond(1.00_s);
const STime STime::oneMinute(1.00_m);
const STime STime::oneHour(1.00_h);
const STime STime::oneDay(1.00_d);
void STime::sleep()
{
	if(milliseconds > 0) SDL_Delay(milliseconds);
}
STime::STime()
	: milliseconds(0)
{
	;
}
STime::STime(const STime& copyConstructor)
	: milliseconds(copyConstructor.milliseconds)
{
	;
}
STime::STime(int64_t nmilliseconds)
	: milliseconds(nmilliseconds)
{
	;
}
STime STime::asMilliseconds(int64_t milliseconds)
{
	return STime(milliseconds);
}
STime STime::asSeconds(double seconds)
{
	return STime(oneSecond * seconds);
}
STime STime::asMinutes(double minutes)
{
	return STime(oneMinute * minutes);
}
STime STime::asHours(double hours)
{
	return STime(oneHour * hours);
}
STime STime::asDays(double days)
{
	return STime(oneDay * days);
}
int64_t STime::getMilliseconds() const
{
	return milliseconds;
}
double STime::getSeconds() const
{
	return double(milliseconds) / 1000.00;
}
void STime::setMilliseconds(int64_t milliseconds)
{
	this->milliseconds = milliseconds;
}
void STime::setSeconds(double seconds)
{
	this->milliseconds = int64_t(seconds * 1000.00);
}

bool STime::operator==(const STime& b) const
{
	return milliseconds == b.milliseconds;
}
bool STime::operator==(int64_t& b) const
{
	return milliseconds == b;
}
bool STime::operator==(double& b) const
{
	return milliseconds == int64_t(b * 1000.00);
}
bool STime::operator!=(const STime& b) const
{
	return milliseconds != b.milliseconds;
}
bool STime::operator!=(int64_t& b) const
{
	return milliseconds != b;
}
bool STime::operator!=(double& b) const
{
	return milliseconds != int64_t(b * 1000.00);
}
bool STime::operator>(const STime& b) const
{
	return milliseconds > b.milliseconds;
}
bool STime::operator>(int64_t& b) const
{
	return milliseconds > b;
}
bool STime::operator>(double& b) const
{
	return milliseconds > int64_t(b * 1000.00);
}
bool STime::operator<(const STime& b) const
{
	return milliseconds < b.milliseconds;
}
bool STime::operator<(int64_t& b) const
{
	return milliseconds < b;
}
bool STime::operator<(double& b) const
{
	return milliseconds < int64_t(b * 1000.00);
}
bool STime::operator>=(const STime& b) const
{
	return milliseconds >= b.milliseconds;
}
bool STime::operator>=(int64_t& b) const
{
	return milliseconds >= b;
}
bool STime::operator>=(double& b) const
{
	return milliseconds >= int64_t(b * 1000.00);
}
bool STime::operator<=(const STime& b) const
{
	return milliseconds <= b.milliseconds;
}
bool STime::operator<=(int64_t& b) const
{
	return milliseconds <= b;
}
bool STime::operator<=(double& b) const
{
	return milliseconds <= int64_t(b * 1000.00);
}

STime& STime::operator=(const STime& b)
{
	setMilliseconds(b.milliseconds);
	return *this;
}
STime& STime::operator=(int64_t b)
{
	setMilliseconds(b);
	return *this;
}
STime& STime::operator=(double b)
{
	setSeconds(b);
	return *this;
}
STime& STime::operator+=(const STime& b)
{
	milliseconds += b.milliseconds;
	return *this;
}
STime& STime::operator+=(int64_t b)
{
	milliseconds += b;
	return *this;
}
STime& STime::operator+=(double b)
{
	milliseconds += int64_t(b * 1000.00);
	return *this;
}
STime& STime::operator-=(const STime& b)
{
	milliseconds -= b.milliseconds;
	return *this;
}
STime& STime::operator-=(int64_t b)
{
	milliseconds -= b;
	return *this;
}
STime& STime::operator-=(double b)
{
	milliseconds -= int64_t(b * 1000.00);
	return *this;
}
STime& STime::operator*=(const STime& b)
{
	milliseconds *= b.milliseconds;
	return *this;
}
STime& STime::operator*=(int64_t b)
{
	milliseconds *= b;
	return *this;
}
STime& STime::operator*=(double b)
{
	milliseconds *= int64_t(b);
	return *this;
}
STime& STime::operator/=(const STime& b)
{
	milliseconds /= b.milliseconds;
	return *this;
}
STime& STime::operator/=(int64_t b)
{
	milliseconds /= b;
	return *this;
}
STime& STime::operator/=(double b)
{
	milliseconds /= int64_t(b);
	return *this;
}
STime& STime::operator%=(const STime& b)
{
	milliseconds %= b.milliseconds;
	return *this;
}
STime& STime::operator%=(int64_t b)
{
	milliseconds %= b;
	return *this;
}
STime& STime::operator%=(double b)
{
	milliseconds %= int64_t(b * 1000.00);
	return *this;
}
STime STime::operator+(const STime& b) const
{
	STime tmp(milliseconds);
	tmp += b;
	return tmp;
}
STime STime::operator+(int64_t b) const
{
	STime tmp(milliseconds);
	tmp += b;
	return tmp;
}
STime STime::operator+(double b) const
{
	STime tmp(milliseconds);
	tmp += b;
	return tmp;
}
STime STime::operator-(const STime& b) const
{
	STime tmp(milliseconds);
	tmp -= b;
	return tmp;
}
STime STime::operator-(int64_t b) const
{
	STime tmp(milliseconds);
	tmp -= b;
	return tmp;
}
STime STime::operator-(double b) const
{
	STime tmp(milliseconds);
	tmp -= b;
	return tmp;
}
STime STime::operator*(const STime& b) const
{
	STime tmp(milliseconds);
	tmp *= b;
	return tmp;
}
STime STime::operator*(int64_t b) const
{
	STime tmp(milliseconds);
	tmp *= b;
	return tmp;
}
STime STime::operator*(double b) const
{
	STime tmp(milliseconds);
	tmp *= b;
	return tmp;
}
STime STime::operator/(const STime& b) const
{
	STime tmp(milliseconds);
	tmp /= b;
	return tmp;
}
STime STime::operator/(int64_t b) const
{
	STime tmp(milliseconds);
	tmp /= b;
	return tmp;
}
STime STime::operator/(double b) const
{
	STime tmp(milliseconds);
	tmp /= b;
	return tmp;
}
STime STime::operator%(const STime& b) const
{
	STime tmp(milliseconds);
	tmp %= b;
	return tmp;
}
STime STime::operator%(int64_t b) const
{
	STime tmp(milliseconds);
	tmp %= b;
	return tmp;
}
STime STime::operator%(double b) const
{
	STime tmp(milliseconds);
	tmp %= b;
	return tmp;
}
