#ifndef SOUNDBUFFER_HPP
#define SOUNDBUFFER_HPP
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(SoundBuffer)
class SoundBuffer : public AudioBuffer
{
private:
	const int format,channelCount,samplerate;
	const sf_count_t frameCount;
	SoundBuffer(sSoundFile src);
	SoundBuffer(const SoundBuffer&);
	SoundBuffer& operator=(const SoundBuffer&);
public:
	static sAudioBuffer createSoundBuffer(sSoundFile src);
	int getFormat();
	int getChannelCount();
	int getSamplerate();
	sf_count_t getFrameCount();
protected:
	const char* getClassName();
};

}
#endif // SOUNDBUFFER_HPP
