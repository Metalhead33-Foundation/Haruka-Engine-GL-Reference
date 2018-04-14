#include "AuxiliaryEffectSlot.hpp"

namespace Audio {

AuxiliaryEffectSlot::AuxiliaryEffectSlot()
{
	alGenAuxiliaryEffectSlots(1,&auxiliaryeffectslot);
}
AuxiliaryEffectSlot::AuxiliaryEffectSlot(const AuxiliaryEffectSlot& cpy)
{
	alGenAuxiliaryEffectSlots(1,&auxiliaryeffectslot);
	effect = cpy.effect;
	filter = cpy.filter;
}
sAuxiliaryEffectSlot AuxiliaryEffectSlot::create()
{
	return sAuxiliaryEffectSlot(new AuxiliaryEffectSlot());
}
sAuxiliaryEffectSlot AuxiliaryEffectSlot::create(sAuxiliaryEffectSlot cpy)
{
	if(cpy) return sAuxiliaryEffectSlot(new AuxiliaryEffectSlot(*cpy));
	else return sAuxiliaryEffectSlot(new AuxiliaryEffectSlot());
}
AuxiliaryEffectSlot::~AuxiliaryEffectSlot()
{
	alDeleteAuxiliaryEffectSlots(1,&auxiliaryeffectslot);
}
ALuint& AuxiliaryEffectSlot::getAuxiliaryEffectSlot()
{
	return auxiliaryeffectslot;
}
void AuxiliaryEffectSlot::setGain(float gain)
{
	alAuxiliaryEffectSlotf(auxiliaryeffectslot,AL_EFFECTSLOT_GAIN,gain);
}
float AuxiliaryEffectSlot::getGain(void) const
{
	float tmp;
	alGetAuxiliaryEffectSlotf(auxiliaryeffectslot,AL_EFFECTSLOT_GAIN,&tmp);
	return tmp;
}
void AuxiliaryEffectSlot::setSendAudio(bool setto)
{
	alAuxiliaryEffectSloti(auxiliaryeffectslot,AL_EFFECTSLOT_AUXILIARY_SEND_AUTO,setto);
}
bool AuxiliaryEffectSlot::getSendAudio(void) const
{
	int tmp;
	alGetAuxiliaryEffectSloti(auxiliaryeffectslot,AL_EFFECTSLOT_AUXILIARY_SEND_AUTO,&tmp);
	return tmp != 0;
}
void AuxiliaryEffectSlot::setEffect(sEffect eff)
{
	effect = eff;
	if(effect) alAuxiliaryEffectSloti(auxiliaryeffectslot,AL_EFFECTSLOT_EFFECT,effect->getEffect());
	else alAuxiliaryEffectSloti(auxiliaryeffectslot,AL_EFFECTSLOT_EFFECT,AL_EFFECT_NULL);
}
sEffect AuxiliaryEffectSlot::getEffect() const
{
	return effect;
}
void AuxiliaryEffectSlot::setFilter(sFilter flt)
{
	filter = flt;
}
sFilter AuxiliaryEffectSlot::getFilter() const
{
	return filter;
}
void AuxiliaryEffectSlot::applyToSource(ALuint& source)
{
	if(effect)
	{
		if(filter) alSource3i(source,AL_AUXILIARY_SEND_FILTER, auxiliaryeffectslot, 0, filter->getFilter());
		else alSource3i(source,AL_AUXILIARY_SEND_FILTER, auxiliaryeffectslot, 0, AL_FILTER_NULL);
	}
}

}
