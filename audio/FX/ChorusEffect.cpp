#include "ChorusEffect.hpp"

namespace Audio {

ChorusEffect::ChorusEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_CHORUS);
}

ALenum ChorusEffect::getEffectType()
{
	return AL_EFFECT_CHORUS;
}
void ChorusEffect::setIsWaveformTriangle(bool isWaveformTriangle)
{
	alEffecti(effectID,AL_CHORUS_WAVEFORM, isWaveformTriangle);
}
bool ChorusEffect::getIsWaveformTriangle(void) const
{
	int tmp;
	alGetEffecti(effectID,AL_CHORUS_WAVEFORM,&tmp);
	return tmp != 0;
}
void ChorusEffect::setPhase(int phase)
{
	alEffecti(effectID,AL_CHORUS_PHASE, phase);
}
int ChorusEffect::getPhase(void) const
{
	int tmp;
	alGetEffecti(effectID,AL_CHORUS_PHASE,&tmp);
	return tmp;
}
void ChorusEffect::setRate(float rate)
{
	alEffectf(effectID,AL_CHORUS_RATE, rate);
}
float ChorusEffect::getRate(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_CHORUS_RATE,&tmp);
	return tmp;
}
void ChorusEffect::setDepth(float rate)
{
	alEffectf(effectID,AL_CHORUS_DEPTH, rate);
}
float ChorusEffect::getDepth(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_CHORUS_DEPTH,&tmp);
	return tmp;
}
void ChorusEffect::setFeedback(float rate)
{
	alEffectf(effectID,AL_CHORUS_FEEDBACK, rate);
}
float ChorusEffect::getFeedback(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_CHORUS_FEEDBACK,&tmp);
	return tmp;
}
void ChorusEffect::setDelay(const STime& rate)
{
	alEffectf(effectID, AL_CHORUS_DELAY,rate.getSeconds());
}
STime ChorusEffect::getDelay(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_CHORUS_DELAY, &tmp);
	return STime::asSeconds(tmp);
}

}
