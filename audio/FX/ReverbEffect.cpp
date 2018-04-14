#include "ReverbEffect.hpp"
namespace Audio {

ReverbEffect::ReverbEffect()
{
	alEffecti(effectID,AL_EFFECT_TYPE, AL_EFFECT_REVERB);
}

ALenum ReverbEffect::getEffectType()
{
	return AL_EFFECT_REVERB;
}
void ReverbEffect::setDensity(float density)
{
	alEffectf(effectID, AL_REVERB_DENSITY, density);
}
float ReverbEffect::getDensity(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_DENSITY, &tmp);
	return tmp;
}
void ReverbEffect::setDiffusion(float diffusion)
{
	alEffectf(effectID, AL_REVERB_DIFFUSION, diffusion);
}
float ReverbEffect::getDiffusion(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_DIFFUSION, &tmp);
	return tmp;
}
void ReverbEffect::setGain(float gain)
{
	alEffectf(effectID, AL_REVERB_GAIN, gain);
}
float ReverbEffect::getGain(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_GAIN, &tmp);
	return tmp;
}
void ReverbEffect::setHighFrequencyGain(float gain)
{
	alEffectf(effectID, AL_REVERB_GAINHF, gain);
}
float ReverbEffect::getHighFrequencyGain(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_GAINHF, &tmp);
	return tmp;
}
void ReverbEffect::setDecayTime(const STime& time)
{
	alEffectf(effectID, AL_REVERB_DECAY_TIME,time.getSeconds());
}
STime ReverbEffect::getDecayTime(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_DECAY_TIME, &tmp);
	return STime::asSeconds(tmp);
}
void ReverbEffect::setDecayHighFrequencyRatio(float hfratio)
{
	alEffectf(effectID, AL_REVERB_DECAY_HFRATIO, hfratio);
}
float ReverbEffect::getDecayHighFrequencyRatio(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_DECAY_HFRATIO, &tmp);
	return tmp;
}
void ReverbEffect::setReflectionsGain(float gain)
{
	alEffectf(effectID, AL_REVERB_REFLECTIONS_GAIN, gain);
}
float ReverbEffect::getReflectionsGain(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_REFLECTIONS_GAIN, &tmp);
	return tmp;
}
void ReverbEffect::setReflectionsDelay(const STime& time)
{
	alEffectf(effectID, AL_REVERB_REFLECTIONS_DELAY,time.getSeconds());
}
STime ReverbEffect::getReflectionsDelay(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_REFLECTIONS_DELAY, &tmp);
	return STime::asSeconds(tmp);
}
void ReverbEffect::setLateReverbGain(float gain)
{
	alEffectf(effectID, AL_REVERB_LATE_REVERB_GAIN, gain);
}
float ReverbEffect::getLateReverbGain(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_LATE_REVERB_GAIN, &tmp);
	return tmp;
}
void ReverbEffect::setLateReverbDelay(const STime& time)
{
	alEffectf(effectID, AL_REVERB_LATE_REVERB_DELAY,time.getSeconds());
}
STime ReverbEffect::getLateReverbDelay(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_LATE_REVERB_DELAY, &tmp);
	return STime::asSeconds(tmp);
}
void ReverbEffect::setRoomRolloffFactor(float factor)
{
	alEffectf(effectID, AL_REVERB_ROOM_ROLLOFF_FACTOR, factor);
}
float ReverbEffect::getRoomRolloffFactor(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_ROOM_ROLLOFF_FACTOR, &tmp);
	return tmp;
}
void ReverbEffect::setHighFrequencyAirAbsorbtionGain(float gain)
{
	alEffectf(effectID, AL_REVERB_AIR_ABSORPTION_GAINHF, gain);
}
float ReverbEffect::getHighFrequencyAirAbsorbtionGain(void) const
{
	float tmp;
	alGetEffectf(effectID, AL_REVERB_AIR_ABSORPTION_GAINHF, &tmp);
	return tmp;
}
void ReverbEffect::setHighFrequencyDecayLimit(bool limit)
{
	alEffecti(effectID, AL_REVERB_DECAY_HFLIMIT,limit);
}
bool ReverbEffect::setHighFrequencyDecayLimit(void) const
{
	int tmp;
	alGetEffecti(effectID, AL_REVERB_DECAY_HFLIMIT, &tmp);
	return tmp != 0;
}

}
