#ifndef AUXILIARYEVENTSLOT_HPP
#define AUXILIARYEVENTSLOT_HPP
#include "../Audio.hpp"
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
