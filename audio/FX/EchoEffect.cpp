#include "EchoEffect.hpp"

namespace Audio {

EchoEffect::EchoEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_ECHO);
}

ALenum EchoEffect::getEffectType()
{
	return AL_EFFECT_ECHO;
}
void EchoEffect::setDelay(const STime& rate)
{
	alEffectf(effectID, AL_ECHO_DELAY,rate.getSeconds());
}
STime EchoEffect::getDelay(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_ECHO_DELAY, &tmp);
	return STime::asSeconds(tmp);
}
void EchoEffect::setLRDelay(const STime& rate)
{
	alEffectf(effectID, AL_ECHO_LRDELAY,rate.getSeconds());
}
STime EchoEffect::getLRDelay(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_ECHO_LRDELAY, &tmp);
	return STime::asSeconds(tmp);
}
void EchoEffect::setDamping(float damping)
{
	alEffectf(effectID,AL_ECHO_DAMPING, damping);
}
float EchoEffect::getDamping(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_ECHO_DAMPING,&tmp);
	return tmp;
}
void EchoEffect::setFeedback(float feedback)
{
	alEffectf(effectID,AL_ECHO_FEEDBACK, feedback);
}
float EchoEffect::getFeedback(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_ECHO_FEEDBACK,&tmp);
	return tmp;
}
void EchoEffect::setSpread(float spread)
{
	alEffectf(effectID,AL_ECHO_SPREAD, spread);
}
float EchoEffect::getSpread(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_ECHO_SPREAD,&tmp);
	return tmp;
}

}
