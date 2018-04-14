#include <iostream>
#include <cstdlib>
#include <FreeImagePlus.h>

#include "sys/GameSystem.hpp"
#include "GL/GlRenderingEngine.hpp"
#include "audio/FX/AllEffects.hpp"

using namespace std;
int main(int argc, char *argv[])
{
	PHYSFS_init(argv[0]);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	PhysFS::FileHandle::addToSearchPath("/home/legacy/zene/others/Eurobeat","/",true);
	if(loadAL())
	{
		GameSystem sys(createGlEngine,640,480,48000,32000,"Hello Worold!");
		Audio::sLowpassFilter filter = Audio::LowpassFilter::create();
		filter->setGain(0.99f);
		filter->setHighFrequencyGain(0.11f);
		std::cout << alGetError() << std::endl;
		Audio::sReverbEffect eff = Audio::ReverbEffect::create();
		std::cout << alGetError() << std::endl;
		eff->setGain(0.99f);
		Audio::sAuxiliaryEffectSlot aux = Audio::AuxiliaryEffectSlot::create();
		aux->setGain(0.99f);
		std::cout << alGetError() << std::endl;
		aux->setEffect(eff);
		std::cout << alGetError() << std::endl;
		Audio::sSource maybetonite = sys.createStream("maybetonight.ogg","maybetonight.ogg",4);
		// maybetonite->setAuxiliaryEffectSlot(aux);
		alSource3i(maybetonite->getSource(),AL_AUXILIARY_SEND_FILTER,aux->getAuxiliaryEffectSlot(), 0, filter->getFilter());
		std::cout << alGetError() << std::endl;
		// maybetonite->setFilter(filter);
		std::cout << alGetError() << std::endl;
		maybetonite->setPitch(1.15);
		maybetonite->play();
		sys.run();
	}
	SDL_Quit();
	PHYSFS_deinit();
	return 0;
}
