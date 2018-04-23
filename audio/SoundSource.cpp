#include "SoundSource.hpp"
namespace Audio {

SoundSource::SoundSource()
	: buffer(nullptr)
{
	;
}
SoundSource::SoundSource(sBuffer buffer)
	: buffer(buffer)
{
	if(buffer) alSourcei( source, AL_BUFFER, buffer->getBuffer() );
}
int SoundSource::getFormat()
{
	if(buffer) return buffer->getFormat();
	else return 0;
}
int SoundSource::getChannelCount()
{
	if(buffer) return buffer->getChannelCount();
	else return 0;
}
int SoundSource::getSamplerate()
{
	if(buffer) return buffer->getSamplerate();
	else return 0;
}
sf_count_t SoundSource::getFrameCount()
{
	if(buffer) return buffer->getFrameCount();
	else return 0;
}

void SoundSource::play()
{
	if(buffer)
	{
		alSourcePlay(source);
	}
}
void SoundSource::pause()
{
	if(buffer)
	{
		alSourcePause(source);
	}
}
void SoundSource::stop()
{
	if(buffer)
	{
		alSourceStop(source);
	}
}
void SoundSource::setBuffer(sBuffer buffer)
{
	this->buffer = buffer;
	if(buffer)
	{
		alSourcei( source, AL_BUFFER, buffer->getBuffer() );
	}
}
const sBuffer SoundSource::getBuffer(void) const
{
	return buffer;
}

}
