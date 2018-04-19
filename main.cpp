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
		sys->createShaderModule("modeldispray.fs","modeldispray.fs",Abstract::ShaderModule::FRAGMENT_SHADER);
		sys->createShaderModule("modeldispray.vs","modeldispray.vs",Abstract::ShaderModule::VERTEX_SHADER);
		sys->createShaderModule("widget.fs","widget.fs",Abstract::ShaderModule::FRAGMENT_SHADER);
		sys->createShaderModule("widget.vs","widget.vs",Abstract::ShaderModule::VERTEX_SHADER);
		sys->createShaderProgram("modeldispray");
		sys->createShaderProgram("widget");
		sys->attachShaderModule("modeldispray","modeldispray.fs");
		sys->attachShaderModule("modeldispray","modeldispray.vs");
		sys->attachShaderModule("widget","widget.fs");
		sys->attachShaderModule("widget","widget.vs");
		sys->linkShaders("modeldispray");
		sys->linkShaders("widget");
		sys->createModel("untitled","lizardman_vessel.blend");
		sys->createWidget("widget");
		sys->createTextureFromImage("logos","200px-Le_56_Face.png",Abstract::Texture::texture_diffuse);
		sys->createTextureFromImage("tommy","lizardman_kochog1.jpg",Abstract::Texture::texture_diffuse);
		sys->attachShaderToMesh("untitled.","modeldispray");
		sys->attachTextureToMesh("untitled.","tommy");
		sys->attachTextureToWidget("widget","logos");
		sys->attachShaderToWidget("widget","widget");
		sys->setWidgetPos("widget",200,200);
		sys->setWidgetSize("widget",200,164);
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
		GameSystem sys(createGlEngine,1440,900,48000,32000,"Hello Worold!",60);
		std::thread trd(initialize,&sys);
		sys.run();
		trd.join();
	}
	SDL_Quit();
	PHYSFS_deinit();
	return 0;
}
