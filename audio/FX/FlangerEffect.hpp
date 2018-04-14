#ifndef FLANGEREFFECT_HPP
#define FLANGEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class FlangerEffect : public Effect
{
public:
	FlangerEffect();
	virtual ALenum getEffectType();
};

}
#endif // FLANGEREFFECT_HPP
