#include "GameSystem.hpp"

GameSystem::GameSystem(RENDERING_BACKEND_CONSTRUCTOR engineCreator, int w, int h, int samplerate, size_t audioBufferSize, const char *title)
	: MainSystem(w, h, title),
	  soundsys(Audio::sSystem(new Audio::System(samplerate, audioBufferSize))),
	  engine( engineCreator(window)  )
{

}

GameSystem::error_t GameSystem::update(STime& deltaTime)
{
	soundsys->processStreamedAudio();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::render()
{
	engine->renderFrame();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::startup()
{
	engine->startup();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::cleanup()
{
	engine->cleanup();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::processWindowEvents(const SDL_Event& ev)
{
	switch (ev.type)
	{
		case SDL_WINDOWEVENT:
		{
			switch(ev.window.event)
			{
				case SDL_WINDOWEVENT_CLOSE:
					return SYSTEM_EXIT;
					break;
				default:
					break;
			}
			break;
		}
		case SDL_KEYDOWN:
		{
			switch(ev.key.keysym.sym)
			{
			default: break;
			}
			break;
		}
	default:
		break;
	}
	return SYSTEM_OKAY;
}
