#pragma once
#include "Global.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

namespace Abstract {

DEFINE_STRUCT(SettingContainer)
struct SettingContainer {
	SDL_Window* window;
	SDL_SysWMinfo* sysWMinfo;
	int w, h;
	const char *title;
};

}
