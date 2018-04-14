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

}
