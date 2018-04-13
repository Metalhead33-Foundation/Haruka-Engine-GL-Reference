#include "StreamedAudio.hpp"
#include "Context.hpp"
#include <iostream>
#include <SDL2/SDL_timer.h>
#include "AudioUtil.hpp"

namespace Audio {

StreamedAudio::StreamedAudio(sSoundFile src, size_t buffNum)
	: soundfile(src), framePosition(0), format(ChannelCount2Format(src->channels())), buffers(buffNum)
{
	alGenBuffers(buffers.size(), buffers.data());
}
StreamedAudio::~StreamedAudio()
{
	alDeleteBuffers(buffers.size(), buffers.data());
}
void StreamedAudio::bufferStart(SoundFile::FrameVector& tmpBuff)
{
	reset();
	size_t tmpCtr;
	for(auto it = buffers.begin(); it != buffers.end(); ++it)
	{
		tmpCtr = soundfile->bufferSound(tmpBuff, &framePosition);
		alBufferData(*it, format, tmpBuff.data(), tmpCtr * soundfile->channels() * sizeof(SoundItem), soundfile->samplerate());
	}
	alSourceQueueBuffers(source, buffers.size(), buffers.data());
}
void StreamedAudio::bufferOneCycle(SoundFile::FrameVector& tmpBuff)
{
	bool continueFlag = false;
	if(getStatus() != originalStatus && framePosition < soundfile->frames() )
	{
		continueFlag = true;
	}
	ALint processedBuffers = 0;
	ALuint unqueuedBuffer = 0;
	size_t tmpCtr;
	alGetSourcei(source, AL_BUFFERS_PROCESSED, &processedBuffers);
	while(processedBuffers)
	{
		alSourceUnqueueBuffers(source, 1, &unqueuedBuffer);
		tmpCtr = soundfile->bufferSound(tmpBuff, &framePosition);
		alBufferData(unqueuedBuffer, format, tmpBuff.data(), tmpCtr * soundfile->channels() * sizeof(SoundItem), soundfile->samplerate());
		alSourceQueueBuffers(source, 1, &unqueuedBuffer);
		--processedBuffers;
	}
	if(continueFlag) alSourcePlay(source);
	originalStatus = getStatus();
}
void StreamedAudio::play()
{
	alSourcePlay(source);
	originalStatus = getStatus();
}
void StreamedAudio::pause()
{
	alSourcePause(source);
	originalStatus = getStatus();
}
void StreamedAudio::stop()
{
	alSourceStop(source);
	originalStatus = getStatus();
}
void StreamedAudio::reset()
{
	soundfile->seek(0, SEEK_SET);
	framePosition = 0;
}
void StreamedAudio::skipFrames(const STime& taimu)
{
	framePosition = soundfile->skipFrames(taimu);
}

}
