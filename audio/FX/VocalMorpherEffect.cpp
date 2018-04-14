#include "VocalMorpherEffect.hpp"
namespace Audio {

VocalMorpherEffect::VocalMorpherEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_VOCAL_MORPHER);
}

ALenum VocalMorpherEffect::getEffectType()
{
	return AL_EFFECT_VOCAL_MORPHER;
}

}
