#include "MainSystem.hpp"
#include <glm/gtc/matrix_transform.hpp>

MainSystem::MainSystem(int w, int h, const char *title, int intendedFramerate)
	: window(Abstract::sSettingContainer(new Abstract::SettingContainer{ 0, 0, w, h, title })),
	  framerate(STime::asSeconds(double(1.00) / double(intendedFramerate))),
	  screenProjection(glm::ortho(0.0f, float(w), float(h), 0.0f, -1.0f, 1.0f))
{
	window->window = SDL_CreateWindow(window->title,
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 window->w,
									 window->h,
									 SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_INPUT_GRABBED);
	window->sysWMinfo = reinterpret_cast<SDL_SysWMinfo*>(malloc(sizeof(SDL_SysWMinfo)));
	SDL_ShowCursor(SDL_DISABLE);
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
			returner = processWindowEvent(ev, tempTime);
			if(returner != SYSTEM_OKAY) break;
		}
		if(returner == SYSTEM_OKAY) returner = update(tempTime);
		if(returner == SYSTEM_OKAY) returner = render();
		if(tempTime < framerate)
		{
			tempTime = framerate - tempTime;
			tempTime.sleep();
		}
	} while(returner == SYSTEM_OKAY);
	return returner;
}
