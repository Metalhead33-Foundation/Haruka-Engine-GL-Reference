#pragma once
#include "Effect.hpp"
namespace Audio {

DEFINE_CLASS(AuxiliaryEffectSlot)
class AuxiliaryEffectSlot
{
private:
	ALuint auxiliaryeffectslot;
	sEffect effect;
	AuxiliaryEffectSlot();
	AuxiliaryEffectSlot(const AuxiliaryEffectSlot& cpy);
	AuxiliaryEffectSlot(sEffect eff);
public:
	static sAuxiliaryEffectSlot create();
	static sAuxiliaryEffectSlot create(sAuxiliaryEffectSlot cpy);
	static sAuxiliaryEffectSlot create(sEffect eff);
	~AuxiliaryEffectSlot();
	ALuint& getAuxiliaryEffectSlot();

	void setGain(float gain);
	float getGain(void) const;
	void setSendAudio(bool setto);
	bool getSendAudio(void) const;
	void setEffect(sEffect eff);
	sEffect getEffect() const;
};

}
