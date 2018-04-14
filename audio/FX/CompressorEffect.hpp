#ifndef COMPRESSOREFFECT_HPP
#define COMPRESSOREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

class CompressorEffect : public Effect
{
public:
	CompressorEffect();
	virtual ALenum getEffectType();
};

}
#endif // COMPRESSOREFFECT_HPP
