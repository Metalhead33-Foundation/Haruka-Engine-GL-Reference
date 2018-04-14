#include "WahWahEffect.hpp"

namespace Audio {

WahWahEffect::WahWahEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_AUTOWAH);
}
WahWahEffect::WahWahEffect(const WahWahEffect& cpy)
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_AUTOWAH);
	setArtackTime(cpy.getAttackTime());
	setPeakGain(cpy.getPeakGain());
	setReleaseTime(cpy.getReleaseTime());
	setResonance(cpy.getResonance());
}
sWahWahEffect WahWahEffect::create()
{
	return sWahWahEffect(new WahWahEffect());
}
sWahWahEffect WahWahEffect::create(sWahWahEffect cpy)
{
	if(cpy) return sWahWahEffect(new WahWahEffect(*cpy));
	else return sWahWahEffect(new WahWahEffect());
}

ALenum WahWahEffect::getEffectType()
{
	return AL_EFFECT_AUTOWAH;
}
void WahWahEffect::setArtackTime(const STime& time)
{
	alEffectf(effectID, AL_AUTOWAH_ATTACK_TIME,time.getSeconds());
}
STime WahWahEffect::getAttackTime(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_AUTOWAH_ATTACK_TIME, &tmp);
	return STime::asSeconds(tmp);
}
void WahWahEffect::setReleaseTime(const STime& time)
{
	alEffectf(effectID, AL_AUTOWAH_RELEASE_TIME,time.getSeconds());
}
STime WahWahEffect::getReleaseTime(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_AUTOWAH_RELEASE_TIME, &tmp);
	return STime::asSeconds(tmp);
}
void WahWahEffect::setResonance(float resonance)
{
	alEffectf(effectID, AL_AUTOWAH_RESONANCE,resonance);
}
float WahWahEffect::getResonance(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_AUTOWAH_RESONANCE, &tmp);
	return tmp;
}
void WahWahEffect::setPeakGain(float peakGain)
{
	alEffectf(effectID, AL_AUTOWAH_PEAK_GAIN,peakGain);
}
float WahWahEffect::getPeakGain(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_AUTOWAH_PEAK_GAIN, &tmp);
	return tmp;
}

}
