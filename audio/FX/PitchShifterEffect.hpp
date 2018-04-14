#ifndef PITCHSHIFTEREFFECT_HPP
#define PITCHSHIFTEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

DEFINE_CLASS(PitchShifterEffect)
class PitchShifterEffect : public Effect
{
private:
	PitchShifterEffect();
	PitchShifterEffect(const PitchShifterEffect& cpy);
public:
	static sPitchShifterEffect create();
	static sPitchShifterEffect create(sPitchShifterEffect cpy);
	virtual ALenum getEffectType();
	void setCoarseTune(int courseTune);
	int getCoarseTune(void) const;
	void setFineTune(int fineTune);
	int getFineTune(void) const;
};

}
#endif // PITCHSHIFTEREFFECT_HPP
