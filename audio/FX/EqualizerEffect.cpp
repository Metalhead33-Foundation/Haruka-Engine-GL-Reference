#include "EqualizerEffect.hpp"

namespace Audio {

EqualizerEffect::EqualizerEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_EQUALIZER);
}

ALenum EqualizerEffect::getEffectType()
{
	return AL_EFFECT_EQUALIZER;
}

}
