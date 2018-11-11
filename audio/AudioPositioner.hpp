#ifndef AUDIOPOSITIONER_HPP
#define AUDIOPOSITIONER_HPP
#include "AudioUnit.hpp"
#include <Harudio-Engine/Audio/Effect/PositionalPanner.hpp>

namespace Audio {
DEFINE_CLASS(Positioner)
class Positioner : public Playable
{
private:
	const sPositionalPanner panner;
	const sUnit unit;
	Positioner(const sSource src);
	Positioner(const Positioner& cpy, const sSource src);
public:
	const sPositionalPanner getPanner() const;
	const sUnit getUnit() const;
	static sPositioner create(const sSource src);
	static sPositioner create(const sPositioner cpy, const sSource src);

	bool isPlaying() const;
	int getFramerate() const;
	int getChannelCount() const;
	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
};
}
#endif // AUDIOPOSITIONER_HPP
