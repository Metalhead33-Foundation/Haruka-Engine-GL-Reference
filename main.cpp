#include <iostream>
#include <cstdlib>
#include <FreeImagePlus.h>

#include "sys/GameSystem.hpp"
#include "GL/GlRenderingEngine.hpp"

using namespace std;
int main(int argc, char *argv[])
{
	PHYSFS_init(argv[0]);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	PhysFS::FileHandle::addToSearchPath("/home/legacy/zene/others/Eurobeat","/",true);
	if(loadAL())
	{
		GameSystem sys(createGlEngine,640,480,48000,32000,"Hello Worold!");
		sys.run();
	}
	SDL_Quit();
	PHYSFS_deinit();
	return 0;
}
