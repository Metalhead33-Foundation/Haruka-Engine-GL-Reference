#ifndef VOCALMORPHEREFFECT_HPP
#define VOCALMORPHEREFFECT_HPP
#include "WaveformEffect.hpp"
namespace Audio {

class VocalMorpherEffect : public WaveformEffect
{
public:
	VocalMorpherEffect();
	virtual ALenum getEffectType();
	void setWaveform(Waveform waveform);
	Waveform getWaveform(void) const;

	void setPhonemeA(char phonemeA);
	void setPhonemeB(char phonemeB);
	void setCoarseTuneA(char coarseTuneA);
	void setCoarseTuneB(char coarseTuneB);
	void setMorpherRate(float morpherRate);

	char getPhonemeA(void) const;
	char getPhonemeB(void) const;
	char getCoarseTuneA(void) const;
	char getCoarseTuneB(void) const;
	float getMorpherRate(void) const;
};

}
#endif // VOCALMORPHEREFFECT_HPP
