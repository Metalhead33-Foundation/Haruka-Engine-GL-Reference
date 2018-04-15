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
	PhysFS::FileHandle::addToSearchPath("/home/legacy/zene/Jmusic/","/",true);
	if(loadAL())
	{
		GameSystem sys(createGlEngine,640,480,48000,32000,"Hello Worold!");
		Audio::sLowpassFilter filter = Audio::LowpassFilter::create();
		Audio::sLowpassFilter silence = Audio::LowpassFilter::create();
		filter->setGain(0.99f);
		filter->setHighFrequencyGain(0.11f);
		silence->setGain(0.50f);
		silence->setHighFrequencyGain(0.00f);
		Audio::sReverbEffect eff = Audio::ReverbEffect::create();
		eff->setGain(0.99f);
		Audio::sAuxiliaryEffectSlot aux = Audio::AuxiliaryEffectSlot::create();
		aux->setGain(0.99f);
		aux->setEffect(eff);
		aux->setFilter(filter);
		Audio::sSource maybetonite = sys.createStream("flymesohigh.ogg","flymesohigh.ogg",4);
		maybetonite->setAuxiliaryEffectSlot(aux);
		maybetonite->setFilter(silence);
		maybetonite->setPitch(1.15);
		maybetonite->play();
		sys.run();
	}
	SDL_Quit();
	PHYSFS_deinit();
	return 0;
}
