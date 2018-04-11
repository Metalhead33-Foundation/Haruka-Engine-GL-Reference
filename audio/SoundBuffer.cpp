#include "SoundBuffer.hpp"

namespace Audio {

const char* SoundBuffer::getClassName()
{
	return "SoundBuffer";
}
sAudioBuffer SoundBuffer::createSoundBuffer(sSoundFile src)
{
	return sAudioBuffer(new SoundBuffer(src));
}
SoundBuffer::SoundBuffer(sSoundFile src)
	: samplerate(src->samplerate()), channelCount(src->channels()), format(src->format()), frameCount(src->frames())
{
	std::vector<SoundItem> tmpBuff(frameCount * channelCount);
	alGenBuffers( 1, &buffer );
	getSystem()->logError(getClassName(),"SoundBuffer",alGetError());
	src->bufferSound(buffer,tmpBuff,nullptr);
}
SoundBuffer::~SoundBuffer()
{
	alDeleteBuffers( 1, &buffer );
	getSystem()->logError(getClassName(),"~SoundBuffer",alGetError());
}
int SoundBuffer::getFormat()
{
	return format;
}
int SoundBuffer::getChannelCount()
{
	return channelCount;
}
int SoundBuffer::getSamplerate()
{
	return samplerate;
}
sf_count_t SoundBuffer::getFrameCount()
{
	return frameCount;
}

}
