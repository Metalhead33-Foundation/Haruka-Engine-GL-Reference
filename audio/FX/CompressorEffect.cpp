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
void CompressorEffect::turnOn()
{
	alEffecti(effectID,AL_COMPRESSOR_ONOFF, true);
}
void CompressorEffect::turnOff()
{
	alEffecti(effectID,AL_COMPRESSOR_ONOFF, false);
}
bool CompressorEffect::isOn() const
{
	int tmp;
	alGetEffecti(effectID, AL_COMPRESSOR_ONOFF, &tmp);
	return tmp != 0;
}

}
