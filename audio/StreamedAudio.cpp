#include "StreamedAudio.hpp"
namespace Audio {

StreamedAudio::StreamedAudio(sSoundFile src, size_t bufferSize)
	: soundfile(src), inputBuffer(bufferSize), internalCloque(0)
{
	alGenSources( 1, &source );
	alGenBuffers( 1, &buffer );
	alGenBuffers( 1, &reverseBuffer );
	alSourcei( source, AL_BUFFER, buffer );
	alSourcei(source, AL_LOOPING, false);
}
ALenum StreamedAudio::getRawFormat()
{
	switch(getChannelCount())
	{
	case 1:
		return AL_FORMAT_MONO_FLOAT32;
		break;
	case 2:
		return AL_FORMAT_STEREO_FLOAT32;
		break;
	default:
		return AL_FORMAT_MONO_FLOAT32;
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
	alBufferData(bufferref, getRawFormat(), inputBuffer.data(), tmpCtr * getChannelCount() * sizeof(float), getSamplerate());
	return tmpCtr;
}
void StreamedAudio::playFull()
{
	size_t frameNum = getFrameCount();
	size_t readFrames = 0;
	ALuint tmp = buffer;
	ALint isPlaying;
	do {
		readFrames = bufferSound(reverseBuffer);
		buffer = reverseBuffer;
		reverseBuffer = tmp;
		alSourcei( source, AL_BUFFER, buffer );
		alSourcePlay(source);
		do {
			alGetSourcei(source, AL_SOURCE_STATE, &isPlaying);
		} while( isPlaying == AL_PLAYING );
		alSourcei( source, AL_BUFFER, 0 );
	} while( internalCloque < frameNum );
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
