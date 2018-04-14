#ifndef WAHWAHEFFECT_HPP
#define WAHWAHEFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class WahWahEffect : public Effect
{
public:
	WahWahEffect();
	virtual ALenum getEffectType();
};

}
#endif // WAHWAHEFFECT_HPP
