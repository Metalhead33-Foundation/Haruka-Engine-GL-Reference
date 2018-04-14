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

void VocalMorpherEffect::setWaveform(Waveform waveform)
{
	alEffecti(effectID,AL_VOCAL_MORPHER_WAVEFORM,waveform);
}
VocalMorpherEffect::Waveform VocalMorpherEffect::getWaveform(void) const
{
	int tmp;
	alGetEffecti(effectID, AL_VOCAL_MORPHER_WAVEFORM, &tmp);
	return Waveform(tmp);
}

void VocalMorpherEffect::setPhonemeA(char phonemeA)
{
	alEffecti(effectID,AL_VOCAL_MORPHER_PHONEMEA,phonemeA);
}
void VocalMorpherEffect::setPhonemeB(char phonemeB)
{
	alEffecti(effectID,AL_VOCAL_MORPHER_PHONEMEB,phonemeB);
}
void VocalMorpherEffect::setCoarseTuneA(char coarseTuneA)
{
	alEffecti(effectID,AL_VOCAL_MORPHER_PHONEMEA_COARSE_TUNING,coarseTuneA);
}
void VocalMorpherEffect::setCoarseTuneB(char coarseTuneB)
{
	alEffecti(effectID,AL_VOCAL_MORPHER_PHONEMEB_COARSE_TUNING,coarseTuneB);
}
void VocalMorpherEffect::setMorpherRate(float morpherRate)
{
	alEffectf(effectID, AL_VOCAL_MORPHER_RATE, morpherRate);
}

char VocalMorpherEffect::getPhonemeA(void) const
{
	int tmp;
	alGetEffecti(effectID, AL_VOCAL_MORPHER_PHONEMEA, &tmp);
	return char(tmp);
}
char VocalMorpherEffect::getPhonemeB(void) const
{
	int tmp;
	alGetEffecti(effectID, AL_VOCAL_MORPHER_PHONEMEB, &tmp);
	return char(tmp);
}
char VocalMorpherEffect::getCoarseTuneA(void) const
{
	int tmp;
	alGetEffecti(effectID, AL_VOCAL_MORPHER_PHONEMEA_COARSE_TUNING, &tmp);
	return char(tmp);
}
char VocalMorpherEffect::getCoarseTuneB(void) const
{
	int tmp;
	alGetEffecti(effectID, AL_VOCAL_MORPHER_PHONEMEB_COARSE_TUNING, &tmp);
	return char(tmp);
}
float VocalMorpherEffect::getMorpherRate(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_VOCAL_MORPHER_RATE, &tmp);
	return tmp;
}

}
