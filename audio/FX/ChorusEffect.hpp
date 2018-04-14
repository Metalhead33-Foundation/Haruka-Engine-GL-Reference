#ifndef CHORUSEFFECT_HPP
#define CHORUSEFFECT_HPP
#include "Effect.hpp"

namespace Audio {

class ChorusEffect : public Effect
{
public:
	ChorusEffect();
	virtual ALenum getEffectType();
};
}
#endif // CHORUSEFFECT_HPP
