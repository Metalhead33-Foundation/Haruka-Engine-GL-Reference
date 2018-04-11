#ifndef CLOCK_HPP
#define CLOCK_HPP
#include "STime.hpp"

DEFINE_CLASS(Clock)
class Clock
{
private:
	STime internalClock;
	uint32_t lastClick;
	void updateClock();
public:
	Clock();
	Clock(STime& setClockStart);
	STime getElapsedTime();
	STime restart();
};

#endif // CLOCK_HPP
