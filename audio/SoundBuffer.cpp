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
	std::vector<float> tmpBuff(frameCount * channelCount);
	src->readf(tmpBuff.data(),frameCount);
	alGenBuffers( 1, &buffer );
	getSystem()->logError(getClassName(),"SoundBuffer",alGetError());
	switch(channelCount)
	{
	case 1:
		alBufferData( buffer, AL_FORMAT_MONO_FLOAT32, tmpBuff.data(), tmpBuff.size() * sizeof(float), samplerate );
		break;
	case 2:
		alBufferData( buffer, AL_FORMAT_STEREO_FLOAT32, tmpBuff.data(), tmpBuff.size() * sizeof(float), samplerate );
		break;
	default:
		alBufferData( buffer, AL_FORMAT_MONO_FLOAT32, tmpBuff.data(), tmpBuff.size() * sizeof(float), samplerate );
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
