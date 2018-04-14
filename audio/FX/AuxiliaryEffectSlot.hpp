#pragma once
#include "Effect.hpp"
#include "Filter.hpp"
namespace Audio {

DEFINE_CLASS(AuxiliaryEffectSlot)
class AuxiliaryEffectSlot
{
private:
	ALuint auxiliaryeffectslot;
	sEffect effect;
	sFilter filter;
	AuxiliaryEffectSlot();
	AuxiliaryEffectSlot(const AuxiliaryEffectSlot& cpy);
public:
	static sAuxiliaryEffectSlot create();
	static sAuxiliaryEffectSlot create(sAuxiliaryEffectSlot cpy);
	~AuxiliaryEffectSlot();
	ALuint& getAuxiliaryEffectSlot();

	void setGain(float gain);
	float getGain(void) const;
	void setSendAudio(bool setto);
	bool getSendAudio(void) const;
	void setEffect(sEffect eff);
	sEffect getEffect() const;
	void setFilter(sFilter flt);
	sFilter getFilter() const;
	void applyToSource(ALuint& source);
};

}
