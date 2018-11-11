#include "AudioUnit.hpp"
namespace Audio {

bool Unit::isPlaying() const
{
	if(!src) return false;
	else return getOutput()->isPlaying();
}
int Unit::getFramerate() const
{
	return globalFramerate;
}
int Unit::getChannelCount() const
{
	return getOutput()->getChannelCount();
}
long Unit::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	if(!src) return 0;
	else return getOutput()->pullAudio(output,maxFrameNum,channelNum,frameRate);
}
void Unit::replug()
{
	if(smpl) smpl->setInput(src);
	if(aux)
	{
		if(smpl) aux->setSource(smpl);
		else aux->setSource(src);
	}
}

Unit::Unit(const sSource src)
	: src(src), aux(nullptr), smpl(nullptr)
{
	if(src->getFramerate() != globalFramerate)
	{
		auto tmp = Audio::Resampler::create(0);
		tmp->setInput(src);
		setResampler(tmp);
	}
}
Unit::Unit(const Unit& cpy, const sSource src)
	: src(src), aux(cpy.aux), smpl(nullptr)
{
	if(src->getFramerate() != globalFramerate)
	{
		auto tmp = Audio::Resampler::create(0);
		tmp->setInput(src);
		setResampler(tmp);
	}
}
sUnit Unit::create(const sSource src)
{
	return sUnit(new Unit(src));
}
sUnit Unit::create(const sUnit cpy, const sSource src)
{
	if(cpy) return sUnit(new Unit(*cpy,src));
	else return nullptr;
}
int Unit::globalFramerate = 0;
const sPlayable Unit::getOutput() const
{
	if(aux) return aux;
	else if(smpl) return smpl;
	else return src;
}
const sSource Unit::getSource() const
{
	return src;
}
const sAuxiliaryEffectSlot Unit::getAuxiliaryEffectSlot() const
{
	return aux;
}
const sResampler Unit::getResampler() const
{
	return smpl;
}
void Unit::setSource(sSource setto)
{
	src = setto;
	replug();
}
void Unit::setAuxiliaryEffectSlot(sAuxiliaryEffectSlot setto)
{
	aux = setto;
	replug();
}
void Unit::setResampler(sResampler setto)
{
	smpl = setto;
	replug();
}
void Unit::setSpeed(float setto)
{
	if(setto >= 0.999999f && setto <= 1.000001f && src->getFramerate() == globalFramerate)
	{
		setResampler(nullptr);
	}
	else
	{
		if(smpl) smpl->setSpeed(setto);
		else {
			auto tmp = Audio::Resampler::create(0);
			tmp->setInput(src);
			tmp->setSpeed(setto);
			setResampler(tmp);
		}
	}
}
float Unit::getSpeed() const
{
	if(smpl) return smpl->getSpeed();
	else return 1.0f;
}
void Unit::addEffect(sEffect playable, float wetness)
{
	if(!aux)
	{
		auto tmp = AuxiliaryEffectSlot::create(src->getChannelCount(),globalFramerate);
		setAuxiliaryEffectSlot(tmp);
	}
	aux->addToList(playable,wetness);
}
void Unit::setEffectWetness(float wetness, sEffect playable)
{
	if(!aux) return;
	aux->setWetness(wetness,playable);
}
void Unit::removeEffect(sEffect playable)
{
	if(!aux) return;
	aux->removeFromList(playable);
	if(aux->empty()) setAuxiliaryEffectSlot(nullptr);
}

}
