#ifndef RINGMODULATOREFFECT_HPP
#define RINGMODULATOREFFECT_HPP
#include "WaveformEffect.hpp"
namespace Audio {

class RingModulatorEffect : public WaveformEffect
{
public:
	RingModulatorEffect();
	virtual ALenum getEffectType();
	void setFrequency(float frequency);
	float getFrequency(void) const;
	void setHighpassCutoff(float highpassCutoff);
	float getHighpassCutoff(void) const;
	void setWaveform(Waveform waveform);
	Waveform getWaveform(void) const;
};

}
#endif // RINGMODULATOREFFECT_HPP
