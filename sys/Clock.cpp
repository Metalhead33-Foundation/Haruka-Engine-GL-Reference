#include "Clock.hpp"

Clock::Clock()
	: lastClick(SDL_GetTicks()), internalClock(int64_t(0))
{
	;
}
Clock::Clock(Time& setClockStart)
	: lastClick(SDL_GetTicks()), internalClock(setClockStart)
{

}
void Clock::updateClock()
{
	uint32_t click = SDL_GetTicks();
	internalClock += int64_t(click - lastClick);
	lastClick = click;
}
Time Clock::getElapsedTime()
{
	updateClock();
	return internalClock;
}
Time Clock::restart()
{
	updateClock();
	Time tmp(internalClock.getMilliseconds());
	internalClock.setMilliseconds(0);
	return tmp;
}
