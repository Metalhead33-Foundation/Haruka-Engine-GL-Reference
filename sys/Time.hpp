#ifndef TIME_HPP
#define TIME_HPP
#include "../abstract/Global.hpp"
#include <SDL2/SDL_timer.h>

DEFINE_CLASS(Time)

class Time
{
private:
	uint64_t milliseconds;
public:
	Time();
	Time(Time& copyConstructor);
	Time(uint64_t nmilliseconds);
	Time(double seconds);
	uint64_t getMilliseconds() const;
	double getSeconds() const;
	void setMilliseconds(uint64_t milliseconds);
	void setSeconds(double seconds);
	operator uint64_t() const { return getMilliseconds(); }
	operator double() const { return getSeconds(); }
	void sleep();

	bool operator==(Time& b) const;
	bool operator==(uint64_t& b) const;
	bool operator==(double& b) const;
	bool operator!=(Time& b) const;
	bool operator!=(uint64_t& b) const;
	bool operator!=(double& b) const;
	bool operator>(Time& b) const;
	bool operator>(uint64_t& b) const;
	bool operator>(double& b) const;
	bool operator<(Time& b) const;
	bool operator<(uint64_t& b) const;
	bool operator<(double& b) const;
	bool operator>=(Time& b) const;
	bool operator>=(uint64_t& b) const;
	bool operator>=(double& b) const;
	bool operator<=(Time& b) const;
	bool operator<=(uint64_t& b) const;
	bool operator<=(double& b) const;

	void operator=(Time& b);
	void operator=(uint64_t b);
	void operator=(double b);
	void operator+=(Time& b);
	void operator+=(uint64_t b);
	void operator+=(double b);
	void operator-=(Time& b);
	void operator-=(uint64_t b);
	void operator-=(double b);
	void operator*=(Time& b);
	void operator*=(uint64_t b);
	void operator*=(double b);
	void operator/=(Time& b);
	void operator/=(uint64_t b);
	void operator/=(double b);
	void operator%=(Time& b);
	void operator%=(uint64_t b);
	void operator%=(double b);

	Time operator+(Time& b);
	Time operator+(uint64_t b);
	Time operator+(double b);
	Time operator-(Time& b);
	Time operator-(uint64_t b);
	Time operator-(double b);
	Time operator*(Time& b);
	Time operator*(uint64_t b);
	Time operator*(double b);
	Time operator/(Time& b);
	Time operator/(uint64_t b);
	Time operator/(double b);
	Time operator%(Time& b);
	Time operator%(uint64_t b);
	Time operator%(double b);
};

#endif // TIME_HPP
