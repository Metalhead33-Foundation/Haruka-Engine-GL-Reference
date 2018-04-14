#ifndef WAHWAHEFFECT_HPP
#define WAHWAHEFFECT_HPP
#include "Effect.hpp"
#include "../../sys/STime.hpp"
namespace Audio {

DEFINE_CLASS(WahWahEffect)
class WahWahEffect : public Effect
{
private:
	WahWahEffect();
	WahWahEffect(const WahWahEffect& cpy);
public:
	static sWahWahEffect create();
	static sWahWahEffect create(sWahWahEffect cpy);
	virtual ALenum getEffectType();
	void setArtackTime(const STime& time);
	STime getAttackTime(void) const;
	void setReleaseTime(const STime& time);
	STime getReleaseTime(void) const;
	void setResonance(float resonance);
	float getResonance(void) const;
	void setPeakGain(float peakGain);
	float getPeakGain(void) const;
};

}
#endif // WAHWAHEFFECT_HPP
