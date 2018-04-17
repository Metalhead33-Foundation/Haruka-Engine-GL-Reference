#include <iostream>
#include <cstdlib>
#include <FreeImagePlus.h>

#include "sys/GameSystem.hpp"
#include "GL/GlRenderingEngine.hpp"
#include "audio/FX/AllEffects.hpp"
#include <thread>


using namespace std;

void initialize(GameSystem* sys)
{
	if(sys)
	{
		Audio::sReverbEffect eff = Audio::ReverbEffect::create();
		eff->setGain(0.99f);
		Audio::sAuxiliaryEffectSlot aux = Audio::AuxiliaryEffectSlot::create();
		aux->setGain(0.99f);
		aux->setEffect(eff);
		Audio::sSource maybetonite = sys->createStream("flymesohigh.ogg","flymesohigh.ogg",4);
		maybetonite->setAuxiliaryEffectSlot(aux);
		maybetonite->setPitch(1.15);

		/*sys->createShaderModule("modeldispray.fs","modeldispray.fs",Abstract::ShaderModule::FRAGMENT_SHADER);
		sys->createShaderModule("modeldispray.vs","modeldispray.vs",Abstract::ShaderModule::VERTEX_SHADER);
		Abstract::sShaderProgram moderdispray = sys->createShaderProgram("modeldispray");
		sys->attachShaderModule("modeldispray","modeldispray.fs");
		sys->attachShaderModule("modeldispray","modeldispray.vs");
		moderdispray->linkShaders();
		sys->createModel("untitled","untitled.blend");
		sys->createTextureFromImage("tommy","artist.png",Abstract::Texture::texture_diffuse);
		sys->attachTextureToMesh("untitled.","tommy");
		sys->attachShaderToMesh("untitled.","modeldispray");*/
		maybetonite->play();
	}
}
int main(int argc, char *argv[])
{
	PHYSFS_init(argv[0]);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	PhysFS::FileHandle::addToSearchPath("/home/legacy/zene/Jmusic/","/",true);
	PhysFS::FileHandle::addToSearchPath("/home/metalhead33/printr/other","/",true);
	if(loadAL())
	{
		GameSystem sys(createGlEngine,1440,900,48000,32000,"Hello Worold!");
		sys.createShaderModule("modeldispray.fs","modeldispray.fs",Abstract::ShaderModule::FRAGMENT_SHADER);
		sys.createShaderModule("modeldispray.vs","modeldispray.vs",Abstract::ShaderModule::VERTEX_SHADER);
		Abstract::sShaderProgram moderdispray = sys.createShaderProgram("modeldispray");
		sys.attachShaderModule("modeldispray","modeldispray.fs");
		sys.attachShaderModule("modeldispray","modeldispray.vs");
		moderdispray->linkShaders();
		sys.createModel("untitled","lizardman_vessel.blend");
		sys.createTextureFromImage("tommy","lizardman_kochog1.jpg",Abstract::Texture::texture_diffuse);
		sys.attachTextureToMesh("untitled.","tommy");
		sys.attachShaderToMesh("untitled.","modeldispray");
		std::thread trd(initialize,&sys);
		sys.run();
		trd.join();
	}
	SDL_Quit();
	PHYSFS_deinit();
	return 0;
}
