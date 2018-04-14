#ifndef COMPRESSOREFFECT_HPP
#define COMPRESSOREFFECT_HPP
#include "Effect.hpp"
namespace Audio {

DEFINE_CLASS(CompressorEffect)
class CompressorEffect : public Effect
{
private:
	CompressorEffect();
	CompressorEffect(const CompressorEffect& cpy);
public:
	static sCompressorEffect create();
	static sCompressorEffect create(sCompressorEffect cpy);
	virtual ALenum getEffectType();
	void turnOn();
	void turnOff();
	bool isOn() const;
};

}
#endif // COMPRESSOREFFECT_HPP
