#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <deque>
#include <Harudio-Engine/Audio/AudioContext.hpp>
#include <Harudio-Engine/Sound/SoundStreamer.hpp>
#include <Harudio-Engine/Sound/SoundSource.hpp>
#include "AudioRoom.hpp"
#include "AudioPositioner.hpp"

namespace Audio {

class System
{
public:
	typedef std::deque<Sound::wStreamer> StreamerQueue;
	typedef std::deque<Sound::wSource> SourceQueue;
	typedef std::deque<wPositioner> UnitQueue;
	typedef std::deque<wRoom> RoomQueue;

	typedef StreamerQueue::iterator StreamIterator;
	typedef SourceQueue::iterator SourceIterator;
	typedef UnitQueue::iterator UnitIterator;
	typedef RoomQueue::iterator RoomIterator;
private:
	Context context;
	const size_t streamBuffSize;
	glm::vec3 listenerPos;

	StreamerQueue streams;
	SourceQueue sounds;
	UnitQueue units;
	RoomQueue rooms;
public:
	System(int frequency, size_t buffersize, size_t streamBuffSize);
	void checkStreams();
	void setListenerPosition(const glm::vec3& pos);
};

}

#endif // SYSTEM_HPP
