#include "PitchShifterEffect.hpp"

namespace Audio {

PitchShifterEffect::PitchShifterEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);
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
