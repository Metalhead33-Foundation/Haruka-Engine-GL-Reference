#include "ChorusEffect.hpp"

namespace Audio {

ChorusEffect::ChorusEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_CHORUS);
}

ALenum ChorusEffect::getEffectType()
{
	return AL_EFFECT_CHORUS;
}

}
