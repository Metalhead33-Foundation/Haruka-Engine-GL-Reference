#ifndef STREAMEDAUDIO_HPP
#define STREAMEDAUDIO_HPP
#include "Samplerate.hpp"
#include "../io/SoundFile.hpp"
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(StreamedAudio)
class StreamedAudio : public AudioBuffer, public AudioSource
{
private:
	StreamedAudio(const StreamedAudio&);
	StreamedAudio& operator=(const StreamedAudio&);
	std::vector<SoundItem> inputBuffer;
	size_t framePosition;

	const sSoundFile soundfile;
	ALuint reverseBuffer;
	ThreadPointer runner;
protected:
	const char* getClassName();
	size_t bufferSound(ALuint& bufferref);
	void playFull();
	ALenum getRawFormat();
	static void startStreaming(pStreamedAudio audio);
public:
	~StreamedAudio();
	StreamedAudio(sSoundFile src, size_t bufferSize);
	int getFormat();
	int getChannelCount();
	int getSamplerate();
	sf_count_t getFrameCount();
	void play();
	void pause();
	void stop();
	void reset();
};

}
#endif // STREAMEDAUDIO_HPP
