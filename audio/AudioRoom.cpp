#include "AudioRoom.hpp"
namespace Audio {

bool Room::isPlaying() const
{
	return getOutput()->isPlaying();
}
int Room::getFramerate() const
{
	return Unit::globalFramerate;
}
int Room::getChannelCount() const
{
	return 4;
}
long Room::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	return getOutput()->pullAudio(output,maxFrameNum,channelNum,frameRate);
}
Room::Room()
	: mix(new Mixer(4,Unit::globalFramerate,4*1024))
{
	replug();
}
sRoom Room::create()
{
	return sRoom(new Room());
}

const sMixer Room::getMixer() const
{
	return mix;
}
const sAuxiliaryEffectSlot Room::getAuxiliaryEffectSlot() const
{
	return aux;
}
const FX::sSimpleConvolver Room::getConvolver() const
{
	return conv;
}
const sPlayable Room::getOutput() const
{
	if(aux) return aux;
	else return mix;
}
void Room::setAuxiliaryEffectSlot(sAuxiliaryEffectSlot setto)
{
	aux = setto;
}
void Room::createConvolver()
{
	conv = FX::SimpleConvolver::create(512,4);
	aux = AuxiliaryEffectSlot::create(4,Unit::globalFramerate);
	aux->addToList(conv,1.0f);
}
void Room::destroyConvolver()
{
	conv.reset();
	aux.reset();
	conv = nullptr;
	aux = nullptr;
}

}
