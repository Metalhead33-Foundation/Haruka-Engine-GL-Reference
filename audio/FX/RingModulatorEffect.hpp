#ifndef RINGMODULATOREFFECT_HPP
#define RINGMODULATOREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class RingModulatorEffect : public Effect
{
public:
	RingModulatorEffect();
	virtual ALenum getEffectType();
};

}
#endif // RINGMODULATOREFFECT_HPP
