#ifndef PITCHSHIFTEREFFECT_HPP
#define PITCHSHIFTEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class PitchShifterEffect : public Effect
{
public:
	PitchShifterEffect();
	virtual ALenum getEffectType();
};

}
#endif // PITCHSHIFTEREFFECT_HPP
