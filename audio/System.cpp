#include "System.hpp"
#include "../io/SoundFile.hpp"

namespace Audio {

System::System(int nSamplerate, size_t buffersize)
	: context(sContext(new Context(nSamplerate))), audioBuffer(buffersize)
{

}
void System::makeSystemCurrent()
{
	context->makeCurrent();
}
sStreamedAudio System::createStreamingAudio(Abstract::sFIO reada, size_t buffNum)
{
	Audio::sSoundFile sndfile = Audio::SoundFile::createSoundFile(reada);
	sStreamedAudio tmp = sStreamedAudio(new StreamedAudio(sndfile,buffNum));
	streamedSounds.push_back(tmp);
	return tmp;
}
sBuffer System::createSoundBuffer(Abstract::sFIO reada)
{
	Audio::sSoundFile sndfile = Audio::SoundFile::createSoundFile(reada);
	sBuffer tmp = sBuffer(new SoundBuffer(sndfile));
	buffers.push_back(tmp);
	return tmp;
}
sSoundSource System::createSoundSource()
{
	sSoundSource tmp = sSoundSource(new SoundSource());
	preloadedSounds.push_back(tmp);
	return tmp;
}
sSoundSource System::createSoundSource( sBuffer buffer)
{
	sSoundSource tmp = sSoundSource(new SoundSource(buffer));
	preloadedSounds.push_back(tmp);
	return tmp;
}
void System::processStreamedAudio()
{
	for(StreamingIterator it = streamedSounds.begin(); it != streamedSounds.end(); ++it)
	{
		if((*it)->getStatus() == AL_PLAYING ) (*it)->bufferOneCycle(audioBuffer);
	}
}
void System::processContext()
{
	context->process();
}
void System::suspendContext()
{
	context->suspend();
}

}
