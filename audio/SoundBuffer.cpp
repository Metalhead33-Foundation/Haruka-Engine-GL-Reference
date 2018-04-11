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
	getSystem()->logError(getClassName(),"SoundBuffer",alGetError());
	size_t tmpCtr = src->bufferSound(tmpBuff,nullptr);
	if(src->channels() == 2)
	{
		alBufferData(buffer, STEREO_AUDIO, tmpBuff.data(), tmpCtr * src->channels() * sizeof(SoundItem), src->samplerate());
	}
	else
	{
		alBufferData(buffer, MONO_AUDIO, tmpBuff.data(), tmpCtr * src->channels() * sizeof(SoundItem), src->samplerate());
	}
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
