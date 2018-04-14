#ifndef FREQUENCYSHIFTEREFFECT_HPP
#define FREQUENCYSHIFTEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class FrequencyShifterEffect : public Effect
{
public:
	FrequencyShifterEffect();
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
