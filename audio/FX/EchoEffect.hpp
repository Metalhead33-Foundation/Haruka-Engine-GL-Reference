#ifndef ECHOEFFECT_HPP
#define ECHOEFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class EchoEffect : public Effect
{
public:
	EchoEffect();
	virtual ALenum getEffectType();
};

}
#endif // ECHOEFFECT_HPP
