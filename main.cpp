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
void loadMusic(pGameSystem sys);
void initialize(pGameSystem sys)
{
	std::cout << "[SYSTEM] System Address: [" << sys << "]" << std::endl;
	std::cout << "[SYSTEM] Beginning initialization!" << std::endl;
	std::thread textures(loadTextures, sys);
	std::thread shaders(loadShaders, sys);
	std::thread music(loadMusic, sys);
	textures.join();
	shaders.join();
	music.join();
	std::thread models(loadModels, sys);
	std::thread widgets(loadWidgets, sys);
	models.join();
	widgets.join();
	// sys->wait();
	std::cout << "[SYSTEM] Initialization complete!" << std::endl;
}
int main(int argc, char *argv[])
{
	(void)(argc);
	PHYSFS_init(argv[0]);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	PhysFS::FileHandle::addToSearchPath("/home/legacy/zene/Jmusic/","/",true);
	PhysFS::FileHandle::addToSearchPath("/home/metalhead33/printr/other","/",true);
	if(loadAL())
	{
		Abstract::sFIO frag=nullptr, vert=nullptr;
		frag = PhysFS::FileHandle::openRead("screen.fs");
		vert = PhysFS::FileHandle::openRead("screen.vs");
		GameSystem sys(createGlEngine,1440,900,48000,32000,"Hello Worold!",60,8,8,2,vert,frag);
		std::thread trd(initialize, &sys);
		sys.run();
		trd.join();
	}
	std::cout << "[SYSTEM] Shutdown!" << std::endl;
	SDL_Quit();
	PHYSFS_deinit();
	return 0;
}
void loadModels(pGameSystem sys)
{
	std::cout << "[MODELS] Loading models!" << std::endl;
	ModelProxy vasa("vasa");
	vasa.setLoadPath("lizardman_vessel.blend");
	vasa.attachShader("0", sys->queryShaderProgram("modeldispray"));
	vasa.attachTexture("0", sys->queryTexture("vasa"));
	glm::mat4 modelMatrix;
	// translate it down so it's at the center of the scene
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.75f, 0.0f));
	vasa.setModelPosition(modelMatrix);
	sys->commitModel(vasa);
	std::cout << "[MODELS] Models loaded!" << std::endl;
}
void loadWidgets(pGameSystem sys)
{
	std::cout << "[WIDGETS] Loading widgets!" << std::endl;
	WidgetProxy amerimutt("amerimutt",0);
	amerimutt.setPos(glm::vec2(50,50));
	amerimutt.setShader(sys->queryShaderProgram("widget"));
	if(amerimutt.getShader() == nullptr) std::cout << "Invalid shader!" << std::endl;
	amerimutt.setTexture(sys->queryTexture("amerimutt"));
	amerimutt.defaultSize();
	amerimutt.snapToWidth(300.0f);
	sys->commitWidget(amerimutt);
	std::cout << "[WIDGETS] Widgets loaded!" << std::endl;
}
void loadTextures(pGameSystem sys)
{
	std::cout << "[TEXTURES] Loading textures!" << std::endl;
	std::vector<TextureProxy> textures;
	textures.push_back(TextureProxy("vasa",Abstract::Texture::texture_diffuse, "lizardman_kochog1.jpg"));
	textures.push_back(TextureProxy("amerimutt",Abstract::Texture::texture_diffuse, "200px-Le_56_Face.png"));
	for(auto it = textures.begin(); it != textures.end(); ++it)
	{
		sys->commitTexture(*it);
	}
	STime waiter = STime::asSeconds(0.2);
	waiter.sleep();
	std::cout << "[TEXTURES] Textures loaded!" << std::endl;
}
void loadShaders(pGameSystem sys)
{
	std::cout << "[SHADERS] Loading shaders!" << std::endl;
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
	STime waiter = STime::asSeconds(0.2);
	waiter.sleep();
	std::cout << "[SHADERS] Shaders loaded!" << std::endl;
}
void loadMusic(pGameSystem sys)
{
	// Initialize filters and effects
	LowpassFilterProxy silence("silence");
	LowpassFilterProxy filter("filter");
	ReverbProxy wahwah("wahwah");
	wahwah.setGain(1.00f);
	wahwah.setHighFrequencyGain(1.00f);
	filter.setGain(0.99f);
	filter.setHighFrequencyGain(0.11f);
	silence.setGain(0.00f);
	silence.setHighFrequencyGain(0.00f);
	sys->commitLowpassFilter(silence);
	sys->commitLowpassFilter(filter);
	sys->commitReverbEffect(wahwah);
	// Prep the auxiliary effect slot
	AuxiliaryEffectProxy aux("aux");
	aux.setFilter(sys->queryLowpassFilter("filter"));
	aux.setEffect(sys->queryReverbEffect("wahwah"));
	aux.setGain(1.00f);
	sys->commitAuxiliarySlot(aux);
	SourceProxy music("flymesohigh","flymesohigh.ogg");
	music.setLooping(false);
	music.setPitch(1.12f);
	music.setGain(1.0f);
	music.setFilter(sys->queryLowpassFilter("silence"));
	music.setAuxiliaryEffectSlot(sys->queryAuxiliarySlot("aux"));
	sys->commitSource(music);
	STime waiter = STime::asSeconds(0.2);
	waiter.sleep();
	auto mus = sys->querySource("flymesohigh");
	ReadReference<SourceProxy> buffer(mus);
	if(buffer->getSource())
	{
		std::cout << "Playing sound!" << std::endl;
		buffer->getSource()->play();
	}
	else std::cout << "Invalid audio!" << std::endl;
}
