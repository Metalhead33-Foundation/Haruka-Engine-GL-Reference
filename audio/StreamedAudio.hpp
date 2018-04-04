#ifndef STREAMEDAUDIO_HPP
#define STREAMEDAUDIO_HPP
#include "Samplerate.hpp"
#include "../io/SoundFile.hpp"
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(StreamedAudio)
class StreamedAudio
{
private:
	StreamedAudio(const StreamedAudio&);
	StreamedAudio& operator=(const StreamedAudio&);
	std::vector<float> inputBuffer;
	SRC_DATA dat;

	const sSoundFile source;
	sSamplerate converter;
public:
	StreamedAudio(sSoundFile src);
	virtual size_t generateAudio(std::vector<float>& target, int channels, int sampleRate);
};

}
#endif // STREAMEDAUDIO_HPP
