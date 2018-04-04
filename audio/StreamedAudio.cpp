#include "StreamedAudio.hpp"
namespace Audio {

StreamedAudio::StreamedAudio(sSoundFile src)
	: source(src)
{
	;
}
size_t StreamedAudio::generateAudio(std::vector<float>& target, int channels, int sampleRate)
{
	if(source->samplerate() == sampleRate && channels == source->channels())
	{
		if( (target.size() / channels) < source->frames())
		{
			source->readf( target.data(), target.size() / channels);
			return target.size();
		}
		else
		{
			source->readf( target.data(), source->frames() / channels);
			return source->frames();
		}
	}
	else
	{
		if(channels == source->channels())
		{
			dat.src_ratio = double(sampleRate) / double(source->samplerate());
			inputBuffer.resize( size_t( double(target.size()) / dat.src_ratio) );
			dat.data_in = inputBuffer.data();
			dat.data_out = target.data();
			dat.input_frames = inputBuffer.size() / channels;
			dat.output_frames = target.size() / channels;
			source->readf( inputBuffer.data(), inputBuffer.size() / channels);
			converter->process(&dat);
			return dat.output_frames * channels;
		}
	}
}

}
