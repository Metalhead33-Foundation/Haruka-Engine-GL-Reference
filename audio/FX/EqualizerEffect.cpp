#include "EqualizerEffect.hpp"

namespace Audio {

EqualizerEffect::EqualizerEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_EQUALIZER);
}
EqualizerEffect::EqualizerEffect(const EqualizerEffect& cpy)
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_EQUALIZER);
	setLowGain(cpy.getLowGain());
	setLowCutoff(cpy.getLowCutoff());
	setMid1Gain(cpy.getMid1Gain());
	setMid1Center(cpy.getMid1Center());
	setMid1Width(cpy.getMid1Width());
	setMid2Gain(cpy.getMid2Gain());
	setMid2Center(cpy.getMid2Center());
	setMid2Width(cpy.getMid2Width());
	setHighGain(cpy.getHighGain() );
	setHighCutoff(cpy.getHighCutoff());
}
sEqualizerEffect EqualizerEffect::create()
{
	return sEqualizerEffect(new EqualizerEffect());
}
sEqualizerEffect EqualizerEffect::create(sEqualizerEffect cpy)
{
	if(cpy) return sEqualizerEffect(new EqualizerEffect(*cpy));
	else return sEqualizerEffect(new EqualizerEffect());
}

ALenum EqualizerEffect::getEffectType()
{
	return AL_EFFECT_EQUALIZER;
}
void EqualizerEffect::setLowGain(float lowGain)
{
	alEffectf(effectID,AL_EQUALIZER_LOW_GAIN, lowGain);
}
void EqualizerEffect::setLowCutoff(float lowCutoff)
{
	alEffectf(effectID,AL_EQUALIZER_LOW_CUTOFF, lowCutoff);
}
void EqualizerEffect::setMid1Gain(float mid1Gain)
{
	alEffectf(effectID,AL_EQUALIZER_MID1_GAIN, mid1Gain);
}
void EqualizerEffect::setMid1Center(float mid1Center)
{
	alEffectf(effectID,AL_EQUALIZER_MID1_CENTER, mid1Center);
}
void EqualizerEffect::setMid1Width(float mid1Width)
{
	alEffectf(effectID,AL_EQUALIZER_MID1_WIDTH, mid1Width);
}
void EqualizerEffect::setMid2Gain(float mid1Gain)
{
	alEffectf(effectID,AL_EQUALIZER_MID2_GAIN, mid1Gain);
}
void EqualizerEffect::setMid2Center(float mid1Center)
{
	alEffectf(effectID,AL_EQUALIZER_MID2_CENTER, mid1Center);
}
void EqualizerEffect::setMid2Width(float mid1Width)
{
	alEffectf(effectID,AL_EQUALIZER_MID2_WIDTH, mid1Width);
}
void EqualizerEffect::setHighGain(float highGain)
{
	alEffectf(effectID,AL_EQUALIZER_HIGH_GAIN, highGain);
}
void EqualizerEffect::setHighCutoff(float highCutoff)
{
	alEffectf(effectID,AL_EQUALIZER_HIGH_CUTOFF, highCutoff);
}

float EqualizerEffect::getLowGain(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_LOW_GAIN, &tmp);
	return tmp;
}
float EqualizerEffect::getLowCutoff(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_LOW_CUTOFF, &tmp);
	return tmp;
}
float EqualizerEffect::getMid1Gain(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_MID1_GAIN, &tmp);
	return tmp;
}
float EqualizerEffect::getMid1Center(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_MID1_CENTER, &tmp);
	return tmp;
}
float EqualizerEffect::getMid1Width(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_MID1_WIDTH, &tmp);
	return tmp;
}
float EqualizerEffect::getMid2Gain(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_MID2_GAIN, &tmp);
	return tmp;
}
float EqualizerEffect::getMid2Center(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_MID2_CENTER, &tmp);
	return tmp;
}
float EqualizerEffect::getMid2Width(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_MID2_WIDTH, &tmp);
	return tmp;
}
float EqualizerEffect::getHighGain(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_HIGH_GAIN, &tmp);
	return tmp;
}
float EqualizerEffect::getHighCutoff(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_EQUALIZER_HIGH_CUTOFF, &tmp);
	return tmp;
}

}
