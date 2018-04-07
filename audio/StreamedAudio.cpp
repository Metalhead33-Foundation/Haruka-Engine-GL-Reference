#include "StreamedAudio.hpp"
#include "AudioSystem.hpp"
#include <unistd.h>
#include <iostream>
namespace Audio {

const char* StreamedAudio::getClassName()
{
	return "StreamedAudio";
}
StreamedAudio::StreamedAudio(sSoundFile src, size_t bufferSize)
	: soundfile(src), inputBuffer(bufferSize), internalCloque(0)
{
	alGenSources( 1, &source );
	getSystem()->logError(getClassName(),"StreamedAudio",alGetError());
	alGenBuffers( 1, &buffer );
	getSystem()->logError(getClassName(),"StreamedAudio",alGetError());
	alGenBuffers( 1, &reverseBuffer );
	getSystem()->logError(getClassName(),"StreamedAudio",alGetError());
	// alSourcei( source, AL_BUFFER, buffer );
	// alSourcei(source, AL_LOOPING, false);
	getSystem()->logError(getClassName(),"StreamedAudio",alGetError());
}
ALenum StreamedAudio::getRawFormat()
{
	switch(getChannelCount())
	{
	case 1:
		return MONO_AUDIO;
		break;
	case 2:
		return STEREO_AUDIO;
		break;
	default:
		return MONO_AUDIO;
		break;
	}
}
/*void StreamedAudio::swapBuffers()
{
	ALuint tmp = buffer;
	buffer = reverseBuffer;
	reverseBuffer = tmp;
}*/
StreamedAudio::~StreamedAudio()
{
	alDeleteSources( 1, &source );
	alDeleteBuffers( 1, &buffer );
	alDeleteBuffers( 1, &reverseBuffer );
}
size_t StreamedAudio::bufferSound(ALuint& bufferref)
{
	size_t tmpCtr;
	if( (inputBuffer.size() / getChannelCount()) < soundfile->frames())
	{
		tmpCtr = soundfile->readf( inputBuffer.data(), inputBuffer.size() / getChannelCount());
	}
	else
	{
		tmpCtr = soundfile->readf( inputBuffer.data(), soundfile->frames() / getChannelCount());
	}
	internalCloque += tmpCtr;
	alBufferData(bufferref, getRawFormat(), inputBuffer.data(), tmpCtr * getChannelCount() * sizeof(SoundItem), getSamplerate());
	getSystem()->logError(getClassName(),"bufferSound",alGetError());
	return tmpCtr;
}
void StreamedAudio::playFull()
{
	ALenum lastErr;
	if( (lastErr = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error at the very start! - " << AudioSystem::translateError(lastErr) << std::endl;
	}
	ALuint unqueuedBuffer = 0;
	size_t readFrames = 0;
	size_t frameNum = getFrameCount();
	ALint processedBuffers = 0;
	readFrames = bufferSound(buffer);
	alSourceQueueBuffers(source, 1, &buffer);
	getSystem()->logError(getClassName(),"playFull",alGetError());
	readFrames = bufferSound(reverseBuffer);
	alSourceQueueBuffers(source, 1, &reverseBuffer);
	getSystem()->logError(getClassName(),"playFull",alGetError());
	alSourcePlay(source);
	getSystem()->logError(getClassName(),"playFull",alGetError());
	do {
		usleep(10 * 1000);
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processedBuffers);
		while(processedBuffers)
		{
			alSourceUnqueueBuffers(source, 1, &unqueuedBuffer);
			getSystem()->logError(getClassName(),"playFull",alGetError());
			readFrames = bufferSound(unqueuedBuffer);
			alSourceQueueBuffers(source, 1, &unqueuedBuffer);
			getSystem()->logError(getClassName(),"playFull",alGetError());
			--processedBuffers;
		}
	} while( internalCloque < frameNum && getStatus() == AL_PLAYING);
	reset();
}
int StreamedAudio::getFormat()
{
	return soundfile->format();
}
int StreamedAudio::getChannelCount()
{
	return soundfile->channels();
}
int StreamedAudio::getSamplerate()
{
	return soundfile->samplerate();
}
sf_count_t StreamedAudio::getFrameCount()
{
	return soundfile->frames();
}
void StreamedAudio::play()
{
	playFull();
}
void StreamedAudio::pause()
{
	;
}
void StreamedAudio::stop()
{
	;
}
void StreamedAudio::reset()
{
	soundfile->seek(0, SEEK_SET);
	internalCloque = 0;
}

}
