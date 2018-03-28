#ifndef STREAMEDAUDIO_HPP
#define STREAMEDAUDIO_HPP
#include "Samplerate.hpp"
#include "../io/SoundFile.hpp"
#include <vector>

DEFINE_CLASS(StreamedAudio)
class StreamedAudio
{
private:
	const int inputKHZ,outputKHZ;
	std::vector<uint8_t> inputBuffer,outputBuffer;
	SRC_DATA dat;

	const sSoundFile source;
	sSamplerate converter;
public:
	StreamedAudio(sSoundFile src, int inputSampleRate, int outputSampleRate);
};

#endif // STREAMEDAUDIO_HPP
