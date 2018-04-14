#ifndef WAHWAHEFFECT_HPP
#define WAHWAHEFFECT_HPP
#include "Effect.hpp"
#include "../../sys/STime.hpp"
namespace Audio {

class WahWahEffect : public Effect
{
public:
	WahWahEffect();
	virtual ALenum getEffectType();
	void setATtackTime(const STime& time);
	STime getATtackTime(void) const;
	void setReleaseTime(const STime& time);
	STime getReleaseTime(void) const;
	void setResonance(float resonance);
	float getResonance(void) const;
	void setPeakGain(float peakGain);
	float getPeakGain(void) const;
};

}
#endif // WAHWAHEFFECT_HPP
