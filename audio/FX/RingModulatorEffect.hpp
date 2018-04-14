#ifndef RINGMODULATOREFFECT_HPP
#define RINGMODULATOREFFECT_HPP
#include "WaveformEffect.hpp"
namespace Audio {

DEFINE_CLASS(RingModulatorEffect)
class RingModulatorEffect : public WaveformEffect
{
private:
	RingModulatorEffect();
	RingModulatorEffect(const RingModulatorEffect& cpy);
public:
	static sRingModulatorEffect create();
	static sRingModulatorEffect create(sRingModulatorEffect cpy);
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
