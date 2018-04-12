#ifndef GAMESYSTEM_HPP
#define GAMESYSTEM_HPP
#include "MainSystem.hpp"
#include "../abstract/RenderingEngine.hpp"
#include "../audio/System.hpp"
#include "../io/PhysFsFileHandle.hpp"

class GameSystem : public MainSystem
{
private:
	const Abstract::sRenderingEngine engine;
	const Audio::sSystem soundsys;
public:
	GameSystem(RENDERING_BACKEND_CONSTRUCTOR engineCreator, int w, int h, int samplerate, size_t audioBufferSize, const char* title);
	error_t update(STime& deltaTime);
	error_t render();
	error_t startup();
	error_t cleanup();
	error_t processWindowEvents(const SDL_Event& ev);
};

#endif // GAMESYSTEM_HPP
