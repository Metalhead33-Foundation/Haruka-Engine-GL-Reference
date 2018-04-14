#include "WahWahEffect.hpp"

namespace Audio {

WahWahEffect::WahWahEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_AUTOWAH);
}

ALenum WahWahEffect::getEffectType()
{
	return AL_EFFECT_AUTOWAH;
}

}
