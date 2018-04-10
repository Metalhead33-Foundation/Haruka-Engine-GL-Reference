#ifndef CLOCK_HPP
#define CLOCK_HPP
#include "Time.hpp"

DEFINE_CLASS(Clock)
class Clock
{
private:
	Time internalClock;
	uint32_t lastClick;
	void updateClock();
public:
	Clock();
	Clock(Time& setClockStart);
	Time getElapsedTime();
	Time restart();
};

#endif // CLOCK_HPP
