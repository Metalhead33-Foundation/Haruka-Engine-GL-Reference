#ifndef ECHOEFFECT_HPP
#define ECHOEFFECT_HPP
#include "Effect.hpp"
#include "../../sys/STime.hpp"
namespace Audio {

DEFINE_CLASS(EchoEffect)
class EchoEffect : public Effect
{
private:
	EchoEffect();
	EchoEffect(const EchoEffect& cpy);
public:
	static sEchoEffect create();
	static sEchoEffect create(sEchoEffect cpy);
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
