#ifndef SOUNDBUFFER_HPP
#define SOUNDBUFFER_HPP
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(SoundBuffer)
class SoundBuffer : public Buffer
{
	friend class System;
private:
	const int format,channelCount,samplerate;
	const sf_count_t frameCount;
	SoundBuffer(sSoundFile src);
	SoundBuffer(const SoundBuffer&);
	SoundBuffer& operator=(const SoundBuffer&);
public:
	int getFormat();
	int getChannelCount();
	int getSamplerate();
	sf_count_t getFrameCount();
};

}
#endif // SOUNDBUFFER_HPP
