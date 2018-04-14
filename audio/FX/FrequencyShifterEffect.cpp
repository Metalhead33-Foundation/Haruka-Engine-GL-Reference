#include "FrequencyShifterEffect.hpp"

namespace Audio {

FrequencyShifterEffect::FrequencyShifterEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_FREQUENCY_SHIFTER);
}
FrequencyShifterEffect::FrequencyShifterEffect(const FrequencyShifterEffect& cpy)
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_FREQUENCY_SHIFTER);
	setFrequency(cpy.getFrequency());
	setLeftDirection(cpy.getLeftDirection());
	setRightDirection(cpy.getRightDirection());
}
sFrequencyShifterEffect FrequencyShifterEffect::create()
{
	return sFrequencyShifterEffect(new FrequencyShifterEffect());
}
sFrequencyShifterEffect FrequencyShifterEffect::create(sFrequencyShifterEffect cpy)
{
	if(cpy) return sFrequencyShifterEffect(new FrequencyShifterEffect(*cpy));
	else return sFrequencyShifterEffect(new FrequencyShifterEffect());
}

ALenum FrequencyShifterEffect::getEffectType()
{
	return AL_EFFECT_FREQUENCY_SHIFTER;
}
void FrequencyShifterEffect::setFrequency(float frequency)
{
	alEffectf(effectID,AL_FREQUENCY_SHIFTER_FREQUENCY, frequency);
}
float FrequencyShifterEffect::getFrequency(void) const
{
	float tmp;
	alGetEffectf(effectID,AL_FREQUENCY_SHIFTER_FREQUENCY,&tmp);
	return tmp;
}
void FrequencyShifterEffect::setLeftDirection(int leftDirection)
{
	alEffecti(effectID,AL_FREQUENCY_SHIFTER_LEFT_DIRECTION, leftDirection);
}
int FrequencyShifterEffect::getLeftDirection(void) const
{
	int tmp;
	alGetEffecti(effectID,AL_FREQUENCY_SHIFTER_LEFT_DIRECTION,&tmp);
	return tmp;
}
void FrequencyShifterEffect::setRightDirection(int rightDirection)
{
	alEffecti(effectID,AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION, rightDirection);
}
int FrequencyShifterEffect::getRightDirection(void) const
{
	int tmp;
	alGetEffecti(effectID,AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION,&tmp);
	return tmp;
}

}
