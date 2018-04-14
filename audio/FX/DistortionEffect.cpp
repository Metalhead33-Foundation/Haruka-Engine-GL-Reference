#include "DistortionEffect.hpp"

namespace Audio {

DistortionEffect::DistortionEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_DISTORTION);
}

ALenum DistortionEffect::getEffectType()
{
	return AL_EFFECT_DISTORTION;
}
void DistortionEffect::setEdge(float edge)
{
	alEffectf(effectID,AL_DISTORTION_EDGE, edge);
}
float DistortionEffect::getEdge(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_DISTORTION_EDGE,&tmp);
	return tmp;
}
void DistortionEffect::setGain(float gain)
{
	alEffectf(effectID,AL_DISTORTION_GAIN, gain);
}
float DistortionEffect::getGain(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_DISTORTION_GAIN,&tmp);
	return tmp;
}
void DistortionEffect::setLowPassCutoff(float gain)
{
	alEffectf(effectID,AL_DISTORTION_LOWPASS_CUTOFF, gain);
}
float DistortionEffect::getLowPassCutoff(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_DISTORTION_LOWPASS_CUTOFF,&tmp);
	return tmp;
}
void DistortionEffect::setEQCenter(float gain)
{
	alEffectf(effectID,AL_DISTORTION_EQCENTER, gain);
}
float DistortionEffect::getEQCenter(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_DISTORTION_EQCENTER,&tmp);
	return tmp;
}
void DistortionEffect::setEQBandwith(float gain)
{
	alEffectf(effectID,AL_DISTORTION_EQBANDWIDTH, gain);
}
float DistortionEffect::getEQBandwith(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_DISTORTION_EQBANDWIDTH,&tmp);
	return tmp;
}

}
