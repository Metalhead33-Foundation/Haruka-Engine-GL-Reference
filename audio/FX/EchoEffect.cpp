#include "EchoEffect.hpp"

namespace Audio {

EchoEffect::EchoEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_ECHO);
}

ALenum EchoEffect::getEffectType()
{
	return AL_EFFECT_ECHO;
}

}
