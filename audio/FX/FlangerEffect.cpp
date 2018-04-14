#include "FlangerEffect.hpp"

namespace Audio {

FlangerEffect::FlangerEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_FLANGER);
}

ALenum FlangerEffect::getEffectType()
{
	return AL_EFFECT_FLANGER;
}

void FlangerEffect::setIsWaveformTriangle(bool isWaveformTriangle)
{
	alEffecti(effectID,AL_FLANGER_WAVEFORM, isWaveformTriangle);
}
bool FlangerEffect::getIsWaveformTriangle(void) const
{
	int tmp;
	alGetEffecti(effectID,AL_FLANGER_WAVEFORM,&tmp);
	return tmp != 0;
}
void FlangerEffect::setPhase(int phase)
{
	alEffecti(effectID,AL_FLANGER_PHASE, phase);
}
int FlangerEffect::getPhase(void) const
{
	int tmp;
	alGetEffecti(effectID,AL_FLANGER_PHASE,&tmp);
	return tmp;
}
void FlangerEffect::setRate(float rate)
{
	alEffectf(effectID,AL_FLANGER_RATE, rate);
}
float FlangerEffect::getRate(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_FLANGER_RATE,&tmp);
	return tmp;
}
void FlangerEffect::setDepth(float rate)
{
	alEffectf(effectID,AL_FLANGER_DEPTH, rate);
}
float FlangerEffect::getDepth(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_FLANGER_DEPTH,&tmp);
	return tmp;
}
void FlangerEffect::setFeedback(float rate)
{
	alEffectf(effectID,AL_FLANGER_FEEDBACK, rate);
}
float FlangerEffect::getFeedback(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_FLANGER_FEEDBACK,&tmp);
	return tmp;
}
void FlangerEffect::setDelay(const STime& rate)
{
	alEffectf(effectID, AL_FLANGER_DELAY,rate.getSeconds());
}
STime FlangerEffect::getDelay(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_FLANGER_DELAY, &tmp);
	return STime::asSeconds(tmp);
}

}
