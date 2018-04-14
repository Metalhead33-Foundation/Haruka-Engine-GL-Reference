#ifndef EQUALIZEREFFECT_HPP
#define EQUALIZEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class EqualizerEffect : public Effect
{
public:
	EqualizerEffect();
	virtual ALenum getEffectType();
};

}
#endif // EQUALIZEREFFECT_HPP
