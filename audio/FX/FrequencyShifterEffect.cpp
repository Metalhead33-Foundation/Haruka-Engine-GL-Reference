#include "FrequencyShifterEffect.hpp"

namespace Audio {

FrequencyShifterEffect::FrequencyShifterEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_FREQUENCY_SHIFTER);
}

ALenum FrequencyShifterEffect::getEffectType()
{
	return AL_EFFECT_FREQUENCY_SHIFTER;
}

}
