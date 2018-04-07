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
	src->readf(tmpBuff.data(),frameCount);
	alGenBuffers( 1, &buffer );
	getSystem()->logError(getClassName(),"SoundBuffer",alGetError());
	switch(channelCount)
	{
	case 1:
		alBufferData( buffer, MONO_AUDIO, tmpBuff.data(), tmpBuff.size() * sizeof(SoundItem), samplerate );
		break;
	case 2:
		alBufferData( buffer, STEREO_AUDIO, tmpBuff.data(), tmpBuff.size() * sizeof(SoundItem), samplerate );
		break;
	default:
		alBufferData( buffer, MONO_AUDIO, tmpBuff.data(), tmpBuff.size() * sizeof(SoundItem), samplerate );
		break;
	}
	getSystem()->logError(getClassName(),"SoundBuffer",alGetError());
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
