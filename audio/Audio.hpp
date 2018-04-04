#ifndef AUDIO_HPP
#define AUDIO_HPP
#include "../abstract/Global.hpp"
#include <vector>
namespace Audio {

DEFINE_CLASS(Audio)
class Audio
{
private:
public:
	virtual ~Audio() = default;
	virtual size_t generateAudio(std::vector<float>& target, int channels, int sampleRate) = 0;
};

}
#endif // AUDIO_HPP
