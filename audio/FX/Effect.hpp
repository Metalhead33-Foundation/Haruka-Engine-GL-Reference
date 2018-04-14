#ifndef EFFECT_HPP
#define EFFECT_HPP
#include "../AL/OpenALWrapper.hpp"
#include "../../abstract/Global.hpp"
namespace Audio {

DEFINE_CLASS(Effect)
class Effect
{
protected:
	ALuint effectID;
public:
	Effect();
	virtual ~Effect();
	ALuint& getEffect();
	virtual ALenum getEffectType() = 0;
};

}
#endif // EFFECT_HPP
