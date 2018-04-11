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
	typedef std::deque<sSource> SourceQueue;
	typedef SourceQueue::iterator SourceIterator;
	typedef std::deque<sSoundSource> SoundSourceQueue;
	typedef SoundSourceQueue::iterator SoundSourceIterator;
	typedef std::deque<sStreamedAudio> StreamingQueue;
	typedef StreamingQueue::iterator StreamingIterator;
	typedef std::deque<sBuffer> BufferQueue;
	typedef BufferQueue::iterator BufferIterator;
private:
	std::vector<SoundItem> audioBuffer;
	SoundSourceQueue preloadedSounds;
	StreamingQueue streamedSounds;
	BufferQueue buffers;
public:
	System();
	sStreamedAudio createStreamingAudio(Abstract::sFIO reada, size_t buffNum);
	sBuffer createSoundBuffer(Abstract::sFIO reada);
	sSoundSource createSoundSource();
	sSoundSource createSoundSource(sBuffer buffer);

	void processAudio();
};

}

#endif // SYSTEM_HPP
