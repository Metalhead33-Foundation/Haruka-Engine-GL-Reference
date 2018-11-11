#include "AudioPositioner.hpp"

namespace Audio {
Positioner::Positioner(const sSource src)
	: panner(Audio::PositionalPanner::createPositionPanner()),
	  unit(Unit::create(src))
{
	panner->setInput(unit);
}
Positioner::Positioner(const Positioner& cpy, const sSource src)
	: panner(Audio::PositionalPanner::createPositionPanner()),
	  unit(Unit::create(src))
{
	panner->setInput(unit);
}
const sPositionalPanner Positioner::getPanner() const
{
	return panner;
}
const sUnit Positioner::getUnit() const
{
	return unit;
}
bool Positioner::isPlaying() const
{
	return unit->isPlaying();
}
int Positioner::getFramerate() const
{
	return unit->getFramerate();
}
int Positioner::getChannelCount() const
{
	return 4;
}
long Positioner::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	return panner->pullAudio(output,maxFrameNum,channelNum,frameRate);
}
sPositioner Positioner::create(const sSource src)
{
	return sPositioner(new Positioner(src));
}
sPositioner Positioner::create(const sPositioner cpy, const sSource src)
{
	if(cpy) return sPositioner(new Positioner(*cpy,src));
	else return nullptr;
}

}
