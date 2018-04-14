#ifndef ECHOEFFECT_HPP
#define ECHOEFFECT_HPP
#include "Effect.hpp"
#include "../../sys/STime.hpp"
namespace Audio {

class EchoEffect : public Effect
{
public:
	EchoEffect();
	virtual ALenum getEffectType();
	void setDelay(const STime& rate);
	STime getDelay(void) const;
	void setLRDelay(const STime& rate);
	STime getLRDelay(void) const;
	void setDamping(float damping);
	float getDamping(void) const;
	void setFeedback(float feedback);
	float getFeedback(void) const;
	void setSpread(float spread);
	float getSpread(void) const;
};

}
#endif // ECHOEFFECT_HPP
