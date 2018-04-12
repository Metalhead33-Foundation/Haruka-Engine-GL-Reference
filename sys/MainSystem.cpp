#include "MainSystem.hpp"

MainSystem::MainSystem(int w, int h, const char *title)
	: window(Abstract::sSettingContainer(new Abstract::SettingContainer{ 0, 0, w, h, title }))
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
}
MainSystem::~MainSystem()
{
	SDL_DestroyWindow(window->window);
}

MainSystem::error_t MainSystem::run()
{
	STime tempTime;
	error_t returner = SYSTEM_OKAY;
	if( (returner = startup()) == SYSTEM_ERROR ) return returner;
	clock = sClock(new Clock());
	do
	{
		tempTime = clock->restart();
		while(SDL_PollEvent(&ev))
		{
			returner = processWindowEvents(ev);
			if(returner != SYSTEM_OKAY) break;
		}
		if(returner == SYSTEM_OKAY) returner = update(tempTime);
		if(returner == SYSTEM_OKAY) returner = render();
	} while(returner == SYSTEM_OKAY);
	return returner;
}
