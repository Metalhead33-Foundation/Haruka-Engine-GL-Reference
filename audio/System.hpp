#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include "Audio.hpp"
#include "StreamedAudio.hpp"
#include "SoundSource.hpp"
#include "SoundBuffer.hpp"
#include <deque>

namespace Audio {

class System
{
public:
	typedef std::deque<wSource> SourceQueue;
	typedef SourceQueue::iterator SourceIterator;
	typedef std::deque<wSoundSource> SoundSourceQueue;
	typedef SoundSourceQueue::iterator SoundSourceIterator;
	typedef std::deque<wStreamedAudio> StreamingQueue;
	typedef StreamingQueue::iterator StreamingIterator;
	typedef std::deque<wBuffer> BufferQueue;
	typedef BufferQueue::iterator BufferIterator;
private:
	std::vector<SoundItem> audioBuffer;
	SoundSourceQueue preloadedSounds;
	StreamingQueue streamedSounds;
	BufferQueue buffers;
	const sContext context;
public:
	System(int nSamplerate, size_t buffersize);
	sStreamedAudio createStreamingAudio(Abstract::sFIO reada, size_t buffNum);
	sBuffer createSoundBuffer(Abstract::sFIO reada);
	sSoundSource createSoundSource();
	sSoundSource createSoundSource(sBuffer buffer);

	void makeSystemCurrent();
	void processStreamedAudio();
	void processContext();
	void suspendContext();
};

}

#endif // SYSTEM_HPP
