#pragma once
#include "Samplerate.hpp"
#include "../io/SoundFile.hpp"
#include "Audio.hpp"
namespace Audio {

DEFINE_CLASS(StreamedAudio)
class StreamedAudio : public AudioSource
{
private:
	StreamedAudio(const StreamedAudio&);
	StreamedAudio& operator=(const StreamedAudio&);
	size_t framePosition;

	const sSoundFile soundfile;
	const ALenum format;
	std::vector<ALuint> buffers;
	StreamedAudio(sSoundFile src, size_t buffNum);
protected:
	const char* getClassName();
public:
	static sStreamedAudio create(sSoundFile src, size_t buffNum);
	~StreamedAudio();
	void play();
	void pause();
	void stop();
	void reset();

	void bufferStart(SoundFile::FrameVector& tmpBuff);
	void bufferOneCycle(SoundFile::FrameVector& tmpBuff);
	void skipFrames(const STime& taimu);
};

}
