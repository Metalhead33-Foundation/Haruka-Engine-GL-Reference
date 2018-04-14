#ifndef DISTORTIONEFFECT_HPP
#define DISTORTIONEFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class DistortionEffect : public Effect
{
public:
	DistortionEffect();
	virtual ALenum getEffectType();
	void setEdge(float edge);
	float getEdge(void) const;
	void setGain(float gain);
	float getGain(void) const;
	void setLowPassCutoff(float gain);
	float getLowPassCutoff(void) const;
	void setEQCenter(float gain);
	float getEQCenter(void) const;
	void setEQBandwith(float gain);
	float getEQBandwith(void) const;
};

}
#endif // DISTORTIONEFFECT_HPP
