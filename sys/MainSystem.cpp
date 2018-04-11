#include "MainSystem.hpp"

MainSystem::error_t MainSystem::run()
{
	STime tempTime;
	error_t returner = SYSTEM_OKAY;
	if( (returner = startup()) == SYSTEM_ERROR ) return returner;
	clock = sClock(new Clock());
	do
	{
		tempTime = clock->restart();
		returner = update(tempTime);
		if(returner == SYSTEM_OKAY) returner = render();
	} while(returner == SYSTEM_OKAY);
	return returner;
}
