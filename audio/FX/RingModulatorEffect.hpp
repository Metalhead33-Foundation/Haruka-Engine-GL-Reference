#ifndef RINGMODULATOREFFECT_HPP
#define RINGMODULATOREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class RingModulatorEffect : public Effect
{
public:
	RingModulatorEffect();
	virtual ALenum getEffectType();
	void setFrequency(float frequency);
	float getFrequency(void) const;
	void setHighpassCutoff(float highpassCutoff);
	float getHighpassCutoff(void) const;
	void setWaveform(int waveform);
	int getWaveform(void) const;
};

}
#endif // RINGMODULATOREFFECT_HPP
