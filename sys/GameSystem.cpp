#include "GameSystem.hpp"

GameSystem::GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h, int samplerate, size_t audioBufferSize, const char *title)
	: MainSystem(w, h, title),
	  soundsys(Audio::sSystem(new Audio::System(samplerate, audioBufferSize))),
	  engine(engineCreator(window))
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
Audio::sBuffer GameSystem::createBuffer(const std::string& key, const std::string& path)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Audio::sBuffer tmp = soundsys->createSoundBuffer(riidaa);
	audioBuffers.emplace(key, tmp);
	return tmp;
}
Audio::sSource GameSystem::createStream(const std::string& key, const std::string& path, size_t buffNum)
{
	Abstract::sFIO riidaa = PhysFS::FileHandle::openRead(path);
	Audio::sSource tmp = soundsys->createStreamingAudio(riidaa, buffNum);
	audioSources.emplace(key, tmp);
	return tmp;
}
Audio::sSource GameSystem::createSource(const std::string& key, const std::string& buffkey)
{
	BufferIterator it;
	Audio::sSource tmp;
	if(buffkey.length()) audioBuffers.find(buffkey);
	else it = audioBuffers.end();
	if(it == audioBuffers.end())
	{
		tmp = soundsys->createSoundSource();
	}
	else
	{
		if(it->second.expired())
		{
			tmp = soundsys->createSoundSource();
			audioBuffers.erase(it);
		}
		else
		{
			tmp = soundsys->createSoundSource(it->second.lock());
		}
	}
	audioSources.emplace(key, tmp);
	return tmp;
}
Audio::sBuffer GameSystem::queryBuffer(const std::string& key)
{
	BufferIterator it = audioBuffers.find(key);
	if(it == audioBuffers.end()) return nullptr;
	else return it->second.lock();
}
Audio::sSource GameSystem::querySource(const std::string& key)
{
	SourceIterator it = audioSources.find(key);
	if(it == audioSources.end()) return nullptr;
	else return it->second.lock();
}

GameSystem::error_t GameSystem::processWindowEvent(const SDL_Event& ev)
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
