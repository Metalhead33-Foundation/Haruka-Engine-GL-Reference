#ifndef GAMESYSTEM_HPP
#define GAMESYSTEM_HPP
#include "MainSystem.hpp"
#include "../abstract/RenderingEngine.hpp"
#include "../audio/System.hpp"
#include "../io/PhysFsFileHandle.hpp"
#include <unordered_map>

class GameSystem : public MainSystem
{
public:
	typedef std::unordered_map<std::string, Audio::sBuffer> BufferHash;
	typedef std::unordered_map<std::string, Audio::sSource> SourceHash;
	typedef BufferHash::iterator BufferIterator;
	typedef SourceHash::iterator SourceIterator;
private:
	const Abstract::sRenderingEngine engine;
	const Audio::sSystem soundsys;
	BufferHash audioBuffers;
	SourceHash audioSources;
public:
	GameSystem(RenderingBackendFactoryFunction engineCreator, int w, int h, int samplerate, size_t audioBufferSize, const char* title);
	error_t update(STime& deltaTime);
	error_t render();
	error_t startup();
	error_t cleanup();
	error_t processWindowEvent(const SDL_Event& ev, STime& deltaTime);

	Audio::sBuffer createBuffer(const std::string& key, const std::string& path);
	Audio::sSource createStream(const std::string& key, const std::string& path, size_t buffNum=2);
	Audio::sSource createSource(const std::string& key, const std::string& buffkey);

	Audio::sBuffer queryBuffer(const std::string& key);
	Audio::sSource querySource(const std::string& key);
	void deleteBuffer(const std::string& key);
	void deleteSource(const std::string& key);
};

#endif // GAMESYSTEM_HPP
