#ifndef VOCALMORPHEREFFECT_HPP
#define VOCALMORPHEREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class VocalMorpherEffect : public Effect
{
public:
	VocalMorpherEffect();
	virtual ALenum getEffectType();
};

}
#endif // VOCALMORPHEREFFECT_HPP
