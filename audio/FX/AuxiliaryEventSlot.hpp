#ifndef AUXILIARYEVENTSLOT_HPP
#define AUXILIARYEVENTSLOT_HPP
#include "../AL/OpenALWrapper.hpp"
#include "../../abstract/Global.hpp"
namespace Audio {

DEFINE_CLASS(AuxiliaryEventSlot)
class AuxiliaryEventSlot
{
private:
	ALuint auxiliaryeffectslot;
public:
	AuxiliaryEventSlot();
	~AuxiliaryEventSlot();
	ALuint& geteAuxiliaryEffectSlot();
};

}
#endif // AUXILIARYEVENTSLOT_HPP
