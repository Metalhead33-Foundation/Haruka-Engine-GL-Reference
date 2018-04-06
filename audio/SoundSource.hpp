#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP
#include "Audio.hpp"
namespace Audio {

class SoundSource : public AudioSource
{
private:
	sAudioBuffer buffer;
	SoundSource(const SoundSource&);
	SoundSource& operator=(const SoundSource&);
public:
	SoundSource();
	SoundSource(sAudioBuffer buffer);
	~SoundSource();

	int getFormat();
	int getChannelCount();
	int getSamplerate();
	sf_count_t getFrameCount();

	void play();
	void pause();
	void stop();
	void setBuffer(sAudioBuffer buffer);
};

}
#endif // SOUNDSOURCE_HPP
