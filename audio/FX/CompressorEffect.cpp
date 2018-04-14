#include "CompressorEffect.hpp"

namespace Audio {

CompressorEffect::CompressorEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);
}
CompressorEffect::CompressorEffect(const CompressorEffect& cpy)
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);
	if(cpy.isOn()) turnOn();
	else turnOff();
}
sCompressorEffect CompressorEffect::create()
{
	return sCompressorEffect(new CompressorEffect());
}
sCompressorEffect CompressorEffect::create(sCompressorEffect cpy)
{
	if(cpy) return sCompressorEffect(new CompressorEffect(*cpy));
	else return sCompressorEffect(new CompressorEffect());
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
