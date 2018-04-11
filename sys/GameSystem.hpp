#ifndef GAMESYSTEM_HPP
#define GAMESYSTEM_HPP
#include "MainSystem.hpp"
#include "../abstract/RenderingEngine.hpp"
#include "../audio/Audio.hpp"
#include "../audio/StreamedAudio.hpp"
#include "../io/PhysFsFileHandle.hpp"

class GameSystem : public MainSystem
{
public:
	typedef std::deque<Audio::sStreamedAudio> StreamingQueue;
	typedef StreamingQueue::iterator StreamingIterator;
private:
	Abstract::pRenderingEngine engine;
	const Abstract::sSettingContainer window;
	StreamingQueue streamQueue;
	std::vector<SoundItem> audioBuffer;
	SDL_Event ev;
public:
	GameSystem(RENDERING_BACKEND_CONSTRUCTOR engineCreator, int w, int h, size_t audioBufferSize, const char* title);
	error_t update(STime& deltaTime);
	error_t render();
	error_t startup();
	error_t cleanup();

	Audio::sStreamedAudio startSoundStream(const char* addr, size_t buffNum);
};

#endif // GAMESYSTEM_HPP
