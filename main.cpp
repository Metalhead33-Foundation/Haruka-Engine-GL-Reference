#include <iostream>
#include <cstdlib>
#include <FreeImagePlus.h>

#include "sys/GameSystem.hpp"
#include "GL/GlRenderingEngine.hpp"
#include "audio/FX/AllEffects.hpp"
#include <thread>


using namespace std;

void loadModels(pGameSystem sys);
void loadWidgets(pGameSystem sys);
void loadTextures(pGameSystem sys);
void loadShaders(pGameSystem sys);
void initialize(pGameSystem sys)
{
	std::thread textures(loadTextures, sys);
	std::thread shaders(loadShaders, sys);
	std::thread models(loadModels, sys);
	std::thread widgets(loadWidgets, sys);
	textures.join();
	shaders.join();
	models.join();
	widgets.join();
}
int main(int argc, char *argv[])
{
	PHYSFS_init(argv[0]);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	PhysFS::FileHandle::addToSearchPath("/home/legacy/zene/Jmusic/","/",true);
	PhysFS::FileHandle::addToSearchPath("/home/metalhead33/printr/other","/",true);
	if(loadAL())
	{
		GameSystem sys(createGlEngine,1440,900,48000,32000,"Hello Worold!",60,8);
		std::thread trd(initialize, &sys);
		sys.run();
		trd.join();
	}
	SDL_Quit();
	PHYSFS_deinit();
	return 0;
}
