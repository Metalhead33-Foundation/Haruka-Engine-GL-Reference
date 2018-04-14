#ifndef FREQUENCYSHIFTEREFFECT_HPP
#define FREQUENCYSHIFTEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

DEFINE_CLASS(FrequencyShifterEffect)
class FrequencyShifterEffect : public Effect
{
private:
	FrequencyShifterEffect();
	FrequencyShifterEffect(const FrequencyShifterEffect& cpy);
public:
	static sFrequencyShifterEffect create();
	static sFrequencyShifterEffect create(sFrequencyShifterEffect cpy);
	virtual ALenum getEffectType();
	void setFrequency(float frequency);
	float getFrequency(void) const;
	void setLeftDirection(int leftDirection);
	int getLeftDirection(void) const;
	void setRightDirection(int rightDirection);
	int getRightDirection(void) const;
};

}
#endif // FREQUENCYSHIFTEREFFECT_HPP
