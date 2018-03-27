#include <iostream>
#include "SettingContainer.hpp"
#include "RenderWindow.hpp"
#include <cstdlib>
using namespace std;

int main()
{
	// cout << "Hello World!" << endl;
	bool exit_signal = false;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	sSettingContainer window = sSettingContainer(new SettingContainer{ 0, 0, 640, 400, "Hello Worold!" });
	window->window = SDL_CreateWindow(window->title,
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 window->w,
									 window->h,
									 SDL_WINDOW_ALLOW_HIGHDPI);
	window->sysWMinfo = reinterpret_cast<SDL_SysWMinfo*>(malloc(sizeof(SDL_SysWMinfo)));
	SDL_VERSION(&window->sysWMinfo->version);
	SDL_GetWindowWMInfo(window->window, window->sysWMinfo);
	RenderWindow renderer(window);

	int major,minor;
	glXQueryVersion(window->sysWMinfo->info.x11.display,&major,&minor);
	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLX Version: " << major << "." << minor << std::endl;
	GLfloat calaz[4] = { 0, 0.5, 1, 1 };

	glEnable(GL_DEPTH_TEST);
	glClearColor( calaz[0], calaz[1], calaz[2], calaz[3] );
	glClear( GL_COLOR_BUFFER_BIT );
	SDL_Event ev;
	do {
		while(SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
				case SDL_WINDOWEVENT:
				{
					switch(ev.window.event)
					{
						case SDL_WINDOWEVENT_CLOSE:
							exit_signal = true;
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
					case SDLK_ESCAPE: exit_signal = true; break;
					case SDLK_UP: calaz[0] += 0.3; break;
					case SDLK_DOWN: calaz[0] -= 0.3; break;
					case SDLK_LEFT: calaz[1] += 0.3; break;
					case SDLK_RIGHT: calaz[1] -= 0.3; break;
					default: break;
					}
					break;
				}
			default:
				break;
			}
		}
		glClearColor( calaz[0], calaz[1], calaz[2], calaz[3] );
		glClear(GL_COLOR_BUFFER_BIT);
		renderer.switchBuffers();
	} while(!exit_signal);
	return 0;
}
