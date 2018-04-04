#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP
#include "StreamedAudio.hpp"
#include "PreloadedAudio.hpp"
/* OpenAL headers */
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

namespace Audio {

DEFINE_CLASS(AudioSystem)
class AudioSystem
{
private:
	std::vector<float> buffer;
	ALCdevice* device;
	ALCcontext* context;

	const int sampleRate;
	struct AudioSource
	{
		sAudio sndsrc;
		ALuint buf;
		ALuint src;
	};
	typedef std::vector<AudioSource> SourceVector;
	typedef SourceVector::iterator SourceIterator;
	SourceVector sources;
public:
	AudioSystem(int nSamplerate);
	~AudioSystem();
	void bufferAllSources();
	void playAllSources();
};

}
#endif // AUDIOSYSTEM_HPP
