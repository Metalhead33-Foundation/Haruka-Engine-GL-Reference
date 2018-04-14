#ifndef FLANGEREFFECT_HPP
#define FLANGEREFFECT_HPP
#include "ChorflangEffect.hpp"

namespace Audio {

class FlangerEffect : public ChorflangEffect
{
private:
	FlangerEffect();
	FlangerEffect(const ChorflangEffect& cpy);
public:
	static sChorflangEffect create();
	static sChorflangEffect create(sChorflangEffect cpy);
	virtual ALenum getEffectType();
	void setIsWaveformTriangle(bool isWaveformTriangle);
	bool getIsWaveformTriangle(void) const;
	void setPhase(int phase);
	int getPhase(void) const;
	void setRate(float rate);
	float getRate(void) const;
	void setDepth(float rate);
	float getDepth(void) const;
	void setFeedback(float rate);
	float getFeedback(void) const;
	void setDelay(const STime& rate);
	STime getDelay(void) const;
};

}
#endif // FLANGEREFFECT_HPP
