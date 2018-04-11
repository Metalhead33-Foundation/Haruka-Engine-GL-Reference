#include "Clock.hpp"

Clock::Clock()
	: lastClick(SDL_GetTicks()), internalClock(int64_t(0))
{
	;
}
Clock::Clock(STime& setClockStart)
	: lastClick(SDL_GetTicks()), internalClock(setClockStart)
{

}
void Clock::updateClock()
{
	uint32_t click = SDL_GetTicks();
	internalClock += int64_t(click - lastClick);
	lastClick = click;
}
STime Clock::getElapsedTime()
{
	updateClock();
	return internalClock;
}
STime Clock::restart()
{
	updateClock();
	STime tmp(internalClock.getMilliseconds());
	internalClock.setMilliseconds(0);
	return tmp;
}
