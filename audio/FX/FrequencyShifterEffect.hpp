#ifndef FREQUENCYSHIFTEREFFECT_HPP
#define FREQUENCYSHIFTEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class FrequencyShifterEffect : public Effect
{
public:
	FrequencyShifterEffect();
	virtual ALenum getEffectType();
};

}
#endif // FREQUENCYSHIFTEREFFECT_HPP
