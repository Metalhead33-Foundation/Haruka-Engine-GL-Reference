#include <iostream>
#include <cstdlib>
#include <FreeImagePlus.h>

#include "sys/GameSystem.hpp"
#include "GL/GlRenderingEngine.hpp"
#include "audio/FX/AllEffects.hpp"
#include <thread>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;

void loadModels(pGameSystem sys);
void loadWidgets(pGameSystem sys);
void loadTextures(pGameSystem sys);
void loadShaders(pGameSystem sys);
void initialize(pGameSystem sys)
{
	std::thread textures(loadTextures, sys);
	std::thread shaders(loadShaders, sys);
	textures.join();
	shaders.join();
	std::thread models(loadModels, sys);
	std::thread widgets(loadWidgets, sys);
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
void loadModels(pGameSystem sys)
{
	ModelProxy vasa("vasa");
	vasa.setLoadPath("lizardman_vessel.blend");
	vasa.attachShader("0", sys->queryShaderProgram("modeldispray"));
	vasa.attachTexture("0", sys->queryTexture("vasa"));
	glm::mat4 modelMatrix;
	// translate it down so it's at the center of the scene
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.75f, 0.0f));
	vasa.setModelPosition(modelMatrix);
	sys->commitModel(vasa);
}
void loadWidgets(pGameSystem sys)
{
	WidgetProxy amerimutt("amerimutt",0);
	amerimutt.setSize(glm::vec2(300,300));
	amerimutt.setPos(glm::vec2(300,300));
	amerimutt.setShader(sys->queryShaderProgram("widget"));
	amerimutt.setTexture(sys->queryTexture("amerimutt"));
	sys->commitWidget(amerimutt);
}
void loadTextures(pGameSystem sys)
{
	std::vector<TextureProxy> textures;
	textures.push_back(TextureProxy("vasa",Abstract::Texture::texture_diffuse, "lizardman_kochog1.jpg"));
	textures.push_back(TextureProxy("amerimutt",Abstract::Texture::texture_diffuse, "200px-Le_56_Face.png"));
	for(auto it = textures.begin(); it != textures.end(); ++it)
	{
		sys->commitTexture(*it);
	}
}
void loadShaders(pGameSystem sys)
{
	std::vector<ShaderModuleProxy> modules;
	std::vector<ShaderProgramProxy> programs;
	ShaderProgramProxy prog1("modeldispray");
	ShaderProgramProxy prog2("widget");
	modules.push_back(ShaderModuleProxy("modeldispray.vs",Abstract::ShaderModule::VERTEX_SHADER, "modeldispray.vs"));
	modules.push_back(ShaderModuleProxy("modeldispray.fs",Abstract::ShaderModule::FRAGMENT_SHADER, "modeldispray.fs"));
	for(auto it = modules.begin(); it != modules.end(); ++it)
	{
		prog1.addModule(sys->commitShaderModule(*it));
	}
	sys->commitShaderProgram(prog1);
	modules.clear();
	modules.push_back(ShaderModuleProxy("widget.vs",Abstract::ShaderModule::VERTEX_SHADER, "widget.vs"));
	modules.push_back(ShaderModuleProxy("widget.fs",Abstract::ShaderModule::FRAGMENT_SHADER, "widget.fs"));
	for(auto it = modules.begin(); it != modules.end(); ++it)
	{
		prog2.addModule(sys->commitShaderModule(*it));
	}
	sys->commitShaderProgram(prog2);
	modules.clear();
}
