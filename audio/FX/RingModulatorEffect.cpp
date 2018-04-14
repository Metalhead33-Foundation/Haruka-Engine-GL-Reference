#include "RingModulatorEffect.hpp"
namespace Audio {

RingModulatorEffect::RingModulatorEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_RING_MODULATOR);
}

ALenum RingModulatorEffect::getEffectType()
{
	return AL_EFFECT_RING_MODULATOR;
}
void RingModulatorEffect::setFrequency(float frequency)
{
	alEffectf(effectID, AL_RING_MODULATOR_FREQUENCY, frequency);
}
float RingModulatorEffect::getFrequency(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_RING_MODULATOR_FREQUENCY, &tmp);
	return tmp;
}
void RingModulatorEffect::setHighpassCutoff(float highpassCutoff)
{
	alEffectf(effectID, AL_RING_MODULATOR_HIGHPASS_CUTOFF, highpassCutoff);
}
float RingModulatorEffect::getHighpassCutoff(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_RING_MODULATOR_HIGHPASS_CUTOFF, &tmp);
	return tmp;
}
void RingModulatorEffect::setWaveform(Waveform waveform)
{
	alEffecti(effectID, AL_RING_MODULATOR_WAVEFORM, waveform);
}
RingModulatorEffect::Waveform RingModulatorEffect::getWaveform(void) const
{
	int tmp;
	alGetEffecti(effectID, AL_RING_MODULATOR_WAVEFORM, &tmp);
	return Waveform(tmp);
}

}
