#include "SoundSource.hpp"
namespace Audio {

const char* SoundSource::getClassName()
{
	return "SoundSource";
}
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
		getSystem()->logError(getClassName(),"play",alGetError());
	}
}
void SoundSource::pause()
{
	if(buffer)
	{
		alSourcePause(source);
		getSystem()->logError(getClassName(),"pause",alGetError());
	}
}
void SoundSource::stop()
{
	if(buffer)
	{
		alSourceStop(source);
		getSystem()->logError(getClassName(),"pause",alGetError());
	}
}
void SoundSource::setBuffer(sBuffer buffer)
{
	this->buffer = buffer;
	if(buffer)
	{
		alSourcei( source, AL_BUFFER, buffer->getBuffer() );
		getSystem()->logError(getClassName(),"setBuffer",alGetError());
	}
}

}
