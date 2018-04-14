#ifndef DISTORTIONEFFECT_HPP
#define DISTORTIONEFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class DistortionEffect : public Effect
{
public:
	DistortionEffect();
	virtual ALenum getEffectType();
};

}
#endif // DISTORTIONEFFECT_HPP
