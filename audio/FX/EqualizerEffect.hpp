#ifndef EQUALIZEREFFECT_HPP
#define EQUALIZEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class EqualizerEffect : public Effect
{
public:
	EqualizerEffect();
	virtual ALenum getEffectType();
	void setLowGain(float lowGain);
	void setLowCutoff(float lowCutoff);
	void setMid1Gain(float mid1Gain);
	void setMid1Center(float mid1Center);
	void setMid1Width(float mid1Width);
	void setMid2Gain(float mid1Gain);
	void setMid2Center(float mid1Center);
	void setMid2Width(float mid1Width);
	void setHighGain(float highGain);
	void setHighCutoff(float highCutoff);

	float getLowGain(void) const;
	float getLowCutoff(void) const;
	float getMid1Gain(void) const;
	float getMid1Center(void) const;
	float getMid1Width(void) const;
	float getMid2Gain(void) const;
	float getMid2Center(void) const;
	float getMid2Width(void) const;
	float getHighGain(void) const;
	float getHighCutoff(void) const;
};

}
#endif // EQUALIZEREFFECT_HPP
