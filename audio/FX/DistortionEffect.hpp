#ifndef DISTORTIONEFFECT_HPP
#define DISTORTIONEFFECT_HPP
#include "Effect.hpp"
namespace Audio {

DEFINE_CLASS(DistortionEffect)
class DistortionEffect : public Effect
{
private:
	DistortionEffect();
	DistortionEffect(const DistortionEffect& cpy);
public:
	static sDistortionEffect create();
	static sDistortionEffect create(sDistortionEffect cpy);
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
