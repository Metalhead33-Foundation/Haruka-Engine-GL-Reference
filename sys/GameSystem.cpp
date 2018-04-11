#include "GameSystem.hpp"

GameSystem::GameSystem(RENDERING_BACKEND_CONSTRUCTOR engineCreator, int w, int h, size_t audioBufferSize, const char *title)
	: window(Abstract::sSettingContainer(new Abstract::SettingContainer{ 0, 0, w, h, title })), audioBuffer(audioBufferSize)
{
	window->window = SDL_CreateWindow(window->title,
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 window->w,
									 window->h,
									 SDL_WINDOW_ALLOW_HIGHDPI);
	window->sysWMinfo = reinterpret_cast<SDL_SysWMinfo*>(malloc(sizeof(SDL_SysWMinfo)));
	SDL_VERSION(&window->sysWMinfo->version);
	SDL_GetWindowWMInfo(window->window, window->sysWMinfo);
	engine = engineCreator(window.get());
}

GameSystem::error_t GameSystem::update(STime& deltaTime)
{
	while(SDL_PollEvent(&ev))
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
	};
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
	maybeTonite->play();
	return SYSTEM_OKAY;
}
GameSystem::error_t GameSystem::cleanup()
{
	engine->cleanup();
	delete engine;
	return SYSTEM_OKAY;
}
