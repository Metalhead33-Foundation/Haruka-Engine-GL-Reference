#include "StreamedAudio.hpp"
#include "AudioSystem.hpp"
#include <iostream>
#include <SDL2/SDL_timer.h>

namespace Audio {

const char* StreamedAudio::getClassName()
{
	return "StreamedAudio";
}
StreamedAudio::StreamedAudio(sSoundFile src, size_t bufferSize)
	: soundfile(src), inputBuffer(bufferSize), framePosition(0), runner(nullptr)
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
	if(getStatus() != AL_STOPPED) alSourceStop(source);
	if(runner) runner->join();
	alDeleteSources( 1, &source );
	alDeleteBuffers( 1, &buffer );
	alDeleteBuffers( 1, &reverseBuffer );
}
void StreamedAudio::startStreaming(pStreamedAudio audio)
{
	if(audio) audio->playFull();
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
	readFrames = soundfile->bufferSound(buffer, inputBuffer, &framePosition);
	readFrames = soundfile->bufferSound(reverseBuffer, inputBuffer, &framePosition);
	alSourceQueueBuffers(source, 1, &buffer);
	alSourceQueueBuffers(source, 1, &reverseBuffer);
	alSourcePlay(source);
	getSystem()->logError(getClassName(),"playFull",alGetError());
	do {
		SDL_Delay(uint32_t(float(readFrames / 2) / float(getSamplerate()) * float(1000.00)));
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processedBuffers);
		while(processedBuffers)
		{
			alSourceUnqueueBuffers(source, 1, &unqueuedBuffer);
			getSystem()->logError(getClassName(),"playFull",alGetError());
			readFrames = soundfile->bufferSound(unqueuedBuffer, inputBuffer, &framePosition);
			alSourceQueueBuffers(source, 1, &unqueuedBuffer);
			getSystem()->logError(getClassName(),"playFull",alGetError());
			--processedBuffers;
		}
		if(framePosition >= frameNum && getLooping())
		{
			reset();
		}
	} while( framePosition < frameNum && getStatus() == AL_PLAYING);
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
	if(getStatus() != AL_PLAYING ) runner = ThreadPointer(new std::thread(startStreaming,this));
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
	framePosition = 0;
}

}
