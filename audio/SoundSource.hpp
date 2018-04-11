#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(SoundSource)
class SoundSource : public AudioSource
{
private:
	sAudioBuffer buffer;
	SoundSource(const SoundSource&);
	SoundSource& operator=(const SoundSource&);
public:
	SoundSource();
	SoundSource(sAudioBuffer buffer);

	int getFormat();
	int getChannelCount();
	int getSamplerate();
	sf_count_t getFrameCount();

	void play();
	void pause();
	void stop();
	void setBuffer(sAudioBuffer buffer);
protected:
	const char* getClassName();
};

}
#endif // SOUNDSOURCE_HPP
