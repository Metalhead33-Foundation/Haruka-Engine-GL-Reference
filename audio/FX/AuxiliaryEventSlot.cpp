#include "AuxiliaryEventSlot.hpp"

namespace Audio {

AuxiliaryEventSlot::AuxiliaryEventSlot()
{
	alGenAuxiliaryEffectSlots(1,&auxiliaryeffectslot);
}
AuxiliaryEventSlot::~AuxiliaryEventSlot()
{
	alDeleteAuxiliaryEffectSlots(1,&auxiliaryeffectslot);
}
ALuint& AuxiliaryEventSlot::geteAuxiliaryEffectSlot()
{
	return auxiliaryeffectslot;
}

}
