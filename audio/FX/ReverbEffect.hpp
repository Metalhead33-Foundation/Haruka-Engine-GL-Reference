#ifndef REVERBEFFECT_HPP
#define REVERBEFFECT_HPP
#include "Effect.hpp"
#include "../../sys/STime.hpp"
namespace Audio {

class ReverbEffect : public Effect
{
public:
	ReverbEffect();
	virtual ALenum getEffectType();
	void setDensity(float density);
	float getDensity(void) const;
	void setDiffusion(float diffusion);
	float getDiffusion(void) const;
	void setGain(float gain);
	float getGain(void) const;
	void setHighFrequencyGain(float gain);
	float getHighFrequencyGain(void) const;
	void setDecayTime(const STime& time);
	STime getDecayTime(void) const;
	void setDecayHighFrequencyRatio(float hfratio);
	float getDecayHighFrequencyRatio(void) const;
	void setReflectionsGain(float gain);
	float getReflectionsGain(void) const;
	void setReflectionsDelay(const STime& time);
	STime getReflectionsDelay(void) const;
	void setLateReverbGain(float gain);
	float getLateReverbGain(void) const;
	void setLateReverbDelay(const STime& time);
	STime getLateReverbDelay(void) const;
	void setRoomRolloffFactor(float factor);
	float getRoomRolloffFactor(void) const;
	void setHighFrequencyAirAbsorbtionGain(float gain);
	float getHighFrequencyAirAbsorbtionGain(void) const;
	void setHighFrequencyDecayLimit(bool limit);
	bool setHighFrequencyDecayLimit(void) const;
};

}
#endif // REVERBEFFECT_HPP
