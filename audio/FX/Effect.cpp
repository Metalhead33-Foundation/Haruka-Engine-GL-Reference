#include "Effect.hpp"
namespace Audio {

Effect::Effect()
{
	alGenEffects(1,&effectID);
}
Effect::~Effect()
{
	alDeleteEffects(1,&effectID);
}
ALuint& Effect::getEffect()
{
	return effectID;
}

}
