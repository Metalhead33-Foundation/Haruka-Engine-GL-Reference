#include "PreloadedAudio.hpp"
namespace Audio {


sAudio PreloadedAudio::createPreloadedAudio(sSoundFile src)
{
	return sAudio(new PreloadedAudio(src));
}
sAudio PreloadedAudio::createPreloadedAudio(sSoundFile src, int nsamplerate)
{
	return sAudio(new PreloadedAudio(src,nsamplerate));
}

size_t PreloadedAudio::generateAudio(std::vector<float>& target, int channels, int sampleRate)
{
	return 0;
}

PreloadedAudio::PreloadedAudio(sSoundFile src)
	: samplerate(src->samplerate()), channelCount(src->channels()), format(src->format()), frameCount(src->frames())
{
	container.resize(frameCount);
	src->readf(container.data(),frameCount);
}
PreloadedAudio::PreloadedAudio(sSoundFile src, int nsamplerate)
	: samplerate(nsamplerate > src->samplerate() ? nsamplerate : src->samplerate()), channelCount(src->channels()),
	  format(src->format()), frameCount(src->frames())
{
	if(nsamplerate < src->samplerate())
	{
		converter = sSamplerate(new Samplerate(SRC_LINEAR,src->channels()) );
		std::vector<float> tmpbuf(src->frames());
		src->readf(tmpbuf.data(),src->frames());
		dat.src_ratio = double(nsamplerate) / double(src->samplerate());
		container.resize( size_t( double(tmpbuf.size()) / dat.src_ratio) );
		dat.data_in = tmpbuf.data();
		dat.data_out = container.data();
		dat.input_frames = tmpbuf.size() / channelCount;
		dat.output_frames = container.size() / channelCount;
		converter->process(&dat);
	}
	else {
	container.resize(frameCount);
	src->readf(container.data(),frameCount);
	}
}
size_t generateAudio(std::vector<float>& target, int channels, int sampleRate)
{
	;
}
int PreloadedAudio::getFormat()
{
	return format;
}
int PreloadedAudio::getChannelCount()
{
	return channelCount;
}
int PreloadedAudio::getSamplerate()
{
	return samplerate;
}
sf_count_t PreloadedAudio::getFrameCount()
{
	return frameCount;
}

}
