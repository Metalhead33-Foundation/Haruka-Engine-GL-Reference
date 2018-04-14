#include "RingModulatorEffect.hpp"
namespace Audio {

RingModulatorEffect::RingModulatorEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_RING_MODULATOR);
}

ALenum RingModulatorEffect::getEffectType()
{
	return AL_EFFECT_REVERB;
}

}
