#ifndef CHORFLANGEFFECT_HPP
#define CHORFLANGEFFECT_HPP
#include "Effect.hpp"
#include "../../sys/STime.hpp"

namespace Audio {

DEFINE_CLASS(ChorflangEffect)
class ChorflangEffect : public Effect
{
public:
	virtual ALenum getEffectType() = 0;
	virtual void setIsWaveformTriangle(bool isWaveformTriangle) = 0;
	virtual bool getIsWaveformTriangle(void) const = 0;
	virtual void setPhase(int phase) = 0;
	virtual int getPhase(void) const = 0;
	virtual void setRate(float rate) = 0;
	virtual float getRate(void) const = 0;
	virtual void setDepth(float rate) = 0;
	virtual float getDepth(void) const = 0;
	virtual void setFeedback(float rate) = 0;
	virtual float getFeedback(void) const = 0;
	virtual void setDelay(const STime& rate) = 0;
	virtual STime getDelay(void) const = 0;
};
}
#endif // CHORFLANGEFFECT_HPP
