#include "AudioSystem.hpp"
namespace Audio {

AudioSystem::AudioSystem(int nSamplerate)
	: sampleRate(nSamplerate)
{
	ALCint contextAttr[] = {ALC_FREQUENCY,nSamplerate,0};
	device = alcOpenDevice( NULL );
	context = alcCreateContext( device, contextAttr );
}
AudioSystem::~AudioSystem()
{
	alcDestroyContext( context );
	alcCloseDevice( device );
}
void AudioSystem::bufferAllSources()
{
	for(SourceIterator it = sources.begin(); it != sources.end(); ++it)
	{
		sf_count_t frames = it->sndsrc->generateAudio(buffer,1,sampleRate);
		alBufferData( it->buf, AL_FORMAT_MONO_FLOAT32, buffer.data(), frames * sizeof(float), sampleRate);
		buffer.clear();
		alSourcei(it->src, AL_BUFFER, it->buf);
	}
}
void AudioSystem::playAllSources()
{
	for(SourceIterator it = sources.begin(); it != sources.end(); ++it)
	{
		if(it->src) alSourcePlay(it->src);
	}
}

}
