#include "CompressorEffect.hpp"

namespace Audio {

CompressorEffect::CompressorEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);
}

ALenum CompressorEffect::getEffectType()
{
	return AL_EFFECT_COMPRESSOR;
}

}
