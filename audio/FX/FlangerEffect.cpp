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

}
