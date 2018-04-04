#pragma once
#include "Samplerate.hpp"
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(PreloadedAudio)
class PreloadedAudio : public Audio
{
private:
	PreloadedAudio(const PreloadedAudio&);
	PreloadedAudio& operator=(const PreloadedAudio&);
	std::vector<float> container;
	SRC_DATA dat;

	// const sSoundFile source;
	const int format,channelCount,samplerate;
	const sf_count_t frameCount;
	sSamplerate converter;
	sf_count_t playedFrames;

	PreloadedAudio(sSoundFile src);
	PreloadedAudio(sSoundFile src, int nsamplerate);
public:
	~PreloadedAudio() = default;
	static sAudio createPreloadedAudio(sSoundFile src);
	static sAudio createPreloadedAudio(sSoundFile src, int nsamplerate);
	size_t generateAudio(std::vector<float>& target, int channels, int sampleRate);
	int getFormat();
	int getChannelCount();
	int getSamplerate();
	sf_count_t getFrameCount();
};

}
