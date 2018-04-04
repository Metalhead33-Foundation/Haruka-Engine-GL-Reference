#ifndef AUDIO_HPP
#define AUDIO_HPP
#include "../abstract/Global.hpp"
#include "../io/SoundFile.hpp"
#include <vector>
namespace Audio {

DEFINE_CLASS(Audio)
class Audio
{
private:
public:
	virtual ~Audio() = default;
	virtual size_t generateAudio(std::vector<float>& target, int channels, int sampleRate) = 0;
	virtual int getFormat() = 0;
	virtual int getChannelCount() = 0;
	virtual int getSamplerate() = 0;
	virtual sf_count_t getFrameCount() = 0;
};

}
#endif // AUDIO_HPP
