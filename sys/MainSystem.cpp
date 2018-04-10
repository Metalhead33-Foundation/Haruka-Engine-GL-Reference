#include "MainSystem.hpp"

int MainSystem::run()
{
	Time tempTime;
	int returner = 1;
	if( (returner = startup()) == SYSTEM_ERROR ) return returner;
	clock = sClock(new Clock());
	do
	{
		tempTime = clock->restart().getMilliseconds();
		returner = update(tempTime);
		if(returner == SYSTEM_OKAY) returner = render();
	} while(returner == SYSTEM_OKAY);
	return returner;
}
