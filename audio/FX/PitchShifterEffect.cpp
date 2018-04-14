#include "PitchShifterEffect.hpp"

namespace Audio {

PitchShifterEffect::PitchShifterEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);
}
PitchShifterEffect::PitchShifterEffect(const PitchShifterEffect& cpy)
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);
	setCoarseTune(cpy.getCoarseTune());
	setFineTune(cpy.getFineTune());
}
sPitchShifterEffect PitchShifterEffect::create()
{
	return sPitchShifterEffect(new PitchShifterEffect());
}
sPitchShifterEffect PitchShifterEffect::create(sPitchShifterEffect cpy)
{
	if(cpy) return sPitchShifterEffect(new PitchShifterEffect(*cpy));
	else return sPitchShifterEffect(new PitchShifterEffect());
}

ALenum PitchShifterEffect::getEffectType()
{
	return AL_EFFECT_PITCH_SHIFTER;
}

void PitchShifterEffect::setCoarseTune(int courseTune)
{
	alEffecti(effectID,AL_PITCH_SHIFTER_COARSE_TUNE, courseTune);
}
int PitchShifterEffect::getCoarseTune(void) const
{
	int tmp;
	alGetEffecti(effectID,AL_PITCH_SHIFTER_COARSE_TUNE, &tmp);
	return tmp;
}
void PitchShifterEffect::setFineTune(int fineTune)
{
	alEffecti(effectID,AL_PITCH_SHIFTER_FINE_TUNE, fineTune);
}
int PitchShifterEffect::getFineTune(void) const
{
	int tmp;
	alGetEffecti(effectID,AL_PITCH_SHIFTER_FINE_TUNE, &tmp);
	return tmp;
}

}
