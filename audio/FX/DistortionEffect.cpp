#include "DistortionEffect.hpp"

namespace Audio {

DistortionEffect::DistortionEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_DISTORTION);
}

ALenum DistortionEffect::getEffectType()
{
	return AL_EFFECT_DISTORTION;
}

}
