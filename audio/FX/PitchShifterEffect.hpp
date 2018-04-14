#ifndef PITCHSHIFTEREFFECT_HPP
#define PITCHSHIFTEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class PitchShifterEffect : public Effect
{
public:
	PitchShifterEffect();
	virtual ALenum getEffectType();
	void setCoarseTune(int courseTune);
	int getCoarseTune(void) const;
	void setFineTune(int fineTune);
	int getFineTune(void) const;
};

}
#endif // PITCHSHIFTEREFFECT_HPP
