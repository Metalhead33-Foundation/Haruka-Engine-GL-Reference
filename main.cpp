#include <iostream>
#include "abstract/SettingContainer.hpp"
#include "GL/RenderWindow.hpp"
#include <cstdlib>
#include <FreeImagePlus.h>

#include "io/PhysFsFileHandle.hpp"
#include "audio/StreamedAudio.hpp"
#include "audio/SoundBuffer.hpp"
#include "audio/SoundSource.hpp"
#include "audio/OpenALWrapper.hpp"
using namespace std;

int testStreamedSound();
int testPreloadedSound();
int testRenderer();

int main(int argc, char *argv[])
{
	PHYSFS_init(argv[0]);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	if(loadAL()) testStreamedSound();
	SDL_Quit();
	PHYSFS_deinit();
	return 0;
}

int testStreamedSound()
{
	PhysFS::FileHandle::addToSearchPath("/home/legacy/zene/others/Eurobeat","/",true);
	Audio::AudioResource::initializeSystem(48000);
	Abstract::sFIO file = PhysFS::FileHandle::openRead("Initial D 1st Stage Soundtrack - MAYBE TONITE-kLt-i4IzrT8.ogg");
	Audio::sSoundFile sfile = Audio::SoundFile::createSoundFile(file);
	Audio::StreamedAudio avdio(sfile,32000);
	std::cout << "Channel count: " << avdio.getChannelCount() << std::endl;
	std::cout << "Samplerate: " << avdio.getSamplerate() << std::endl;
	std::cout << "Frame count: " << avdio.getFrameCount() << std::endl;
	avdio.setGain(50);
	avdio.setPitch(1.20f);
	avdio.setRelativity(false);
	avdio.play();
	while(avdio.getStatus() == AL_PLAYING );
	return 0;
}
int testPreloadedSound()
{
	PhysFS::FileHandle::addToSearchPath("/home/legacy/zene/others/other","/",true);
	Audio::AudioResource::initializeSystem(48000);
	Abstract::sFIO file = PhysFS::FileHandle::openRead("the rack.ogg");
	Audio::sSoundFile sfile = Audio::SoundFile::createSoundFile(file);
	Audio::sAudioBuffer buff = Audio::SoundBuffer::createSoundBuffer(sfile);
	Audio::SoundSource avdio(buff);
	std::cout << "Channel count: " << avdio.getChannelCount() << std::endl;
	std::cout << "Samplerate: " << avdio.getSamplerate() << std::endl;
	std::cout << "Frame count: " << avdio.getFrameCount() << std::endl;
	avdio.setGain(100);
	avdio.setRelativity(false);
	avdio.play();
	while(avdio.getStatus() == AL_PLAYING );
	return 0;
}
int testRenderer()
{
	// cout << "Hello World!" << endl;
	bool exit_signal = false;
	Abstract::sSettingContainer window = Abstract::sSettingContainer(new Abstract::SettingContainer{ 0, 0, 640, 400, "Hello Worold!" });
	window->window = SDL_CreateWindow(window->title,
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 window->w,
									 window->h,
									 SDL_WINDOW_ALLOW_HIGHDPI);
	window->sysWMinfo = reinterpret_cast<SDL_SysWMinfo*>(malloc(sizeof(SDL_SysWMinfo)));
	SDL_VERSION(&window->sysWMinfo->version);
	SDL_GetWindowWMInfo(window->window, window->sysWMinfo);
	RenderWindow* renderer = new RenderWindow(window);

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
		renderer->switchBuffers();
	} while(!exit_signal);
	delete renderer;
	return 0;
}
