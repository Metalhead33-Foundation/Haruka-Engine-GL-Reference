#ifndef WAVEFORMEFFECT_HPP
#define WAVEFORMEFFECT_HPP
#include "Effect.hpp"
namespace Audio {

DEFINE_CLASS(WaveformEffect)
class WaveformEffect : public Effect
{
public:
	enum Waveform : int {
		SINE = 0,
		TRIANGLE = 1,
		SAW = 2
	};
	virtual ALenum getEffectType() = 0;
	virtual void setWaveform(Waveform waveform) = 0;
	virtual Waveform getWaveform(void) const = 0;
};

}
#endif // WAVEFORMEFFECT_HPP
