#ifndef STREAMEDAUDIO_HPP
#define STREAMEDAUDIO_HPP
#include "Samplerate.hpp"
#include "../io/SoundFile.hpp"
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(StreamedAudio)
class StreamedAudio : public Audio
{
private:
	StreamedAudio(const StreamedAudio&);
	StreamedAudio& operator=(const StreamedAudio&);
	std::vector<float> inputBuffer;
	SRC_DATA dat;

	const sSoundFile source;
	sSamplerate converter;

	StreamedAudio(sSoundFile src);
public:
	~StreamedAudio() = default;
	static sAudio createStreamedAudio(sSoundFile src);
	virtual size_t generateAudio(std::vector<float>& target, int channels, int sampleRate);
	int getFormat();
	int getChannelCount();
	int getSamplerate();
	sf_count_t getFrameCount();
};

}
#endif // STREAMEDAUDIO_HPP
