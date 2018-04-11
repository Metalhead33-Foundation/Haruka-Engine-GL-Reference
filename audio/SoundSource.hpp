#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(SoundSource)
class SoundSource : public Source
{
	friend class System;
private:
	sBuffer buffer;
	SoundSource(const SoundSource&);
	SoundSource& operator=(const SoundSource&);
	SoundSource();
	SoundSource(sBuffer buffer);
public:
	int getFormat();
	int getChannelCount();
	int getSamplerate();
	sf_count_t getFrameCount();

	void play();
	void pause();
	void stop();
	void setBuffer(sBuffer buffer);
protected:
	const char* getClassName();
};

}
#endif // SOUNDSOURCE_HPP
