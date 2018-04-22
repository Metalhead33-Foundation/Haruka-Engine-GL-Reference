#include "AuxiliaryEffectProxy.hpp"
#include <cstring>

void AuxiliaryEffectProxy::queryData()
{
	if(effectSlot)
	{
		properties.effect = effectSlot->getEffect();
		changedProperties.effect = false;
		properties.filter = effectSlot->getFilter();
		changedProperties.filter = false;
		properties.gain = effectSlot->getGain();
		changedProperties.gain = false;
		properties.sendAudio = effectSlot->getSendAudio();
		changedProperties.sendAudio = false;
	}
}
void AuxiliaryEffectProxy::commitData()
{
	if(effectSlot)
	{
		if(changedProperties.effect)
		{
			effectSlot->setEffect(properties.effect);
			changedProperties.effect = false;
		}
		if(changedProperties.filter)
		{
			effectSlot->setFilter(properties.filter);
			changedProperties.filter = false;
		}
		if(changedProperties.gain)
		{
			effectSlot->setGain(properties.gain);
			changedProperties.gain = false;
		}
		if(changedProperties.sendAudio)
		{
			effectSlot->setSendAudio(properties.sendAudio);
			changedProperties.sendAudio = false;
		}
	}
}
AuxiliaryEffectProxy::AuxiliaryEffectProxy()
	: Proxy(""), effectSlot(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
AuxiliaryEffectProxy::AuxiliaryEffectProxy(const AuxiliaryEffectProxy& cpy)
	: Proxy(cpy.Id), effectSlot(cpy.effectSlot)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
AuxiliaryEffectProxy::AuxiliaryEffectProxy(const std::string& id)
	: Proxy(id), effectSlot(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sAuxiliaryEffectSlot AuxiliaryEffectProxy::getAuxiliaryEffectSlot() const
{
	return effectSlot;
}

void AuxiliaryEffectProxy::setGain(float gain)
{
	properties.gain = gain;
	changedProperties.gain = true;
}
float AuxiliaryEffectProxy::getGain(void) const
{
	return properties.gain;
}
void AuxiliaryEffectProxy::setSendAudio(bool setto)
{
	properties.sendAudio = setto;
	changedProperties.sendAudio = true;
}
bool AuxiliaryEffectProxy::getSendAudio(void) const
{
	return properties.sendAudio;
}
void AuxiliaryEffectProxy::setEffect(const Audio::sEffect eff)
{
	properties.effect = eff;
	changedProperties.effect = true;
}
const Audio::sEffect AuxiliaryEffectProxy::getEffect() const
{
	return properties.effect;
}
void AuxiliaryEffectProxy::setFilter(const Audio::sFilter flt)
{
	properties.filter = flt;
	changedProperties.filter = true;
}
const Audio::sFilter AuxiliaryEffectProxy::getFilter() const
{
	return properties.filter;
}

void AuxiliaryEffectProxy::setEffect(ChorflangReference eff)
{
	ReadReference<ChorflangProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(CompressorReference eff)
{
	ReadReference<CompressorProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(DistortionReference eff)
{
	ReadReference<DistortionProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(EchoReference eff)
{
	ReadReference<EchoProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(EqualizerReference eff)
{
	ReadReference<EqualizerProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(FrequencyShifterReference eff)
{
	ReadReference<FrequencyShifterProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(PitchShifterReference eff)
{
	ReadReference<PitchShifterProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(ReverbReference eff)
{
	ReadReference<ReverbProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(RingModulatorReference eff)
{
	ReadReference<RingModulatorProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(VocalMorpherReference eff)
{
	ReadReference<VocalMorpherProxy> effect(eff);
	setEffect(effect->getEffect());
}
void AuxiliaryEffectProxy::setEffect(WahWahReference eff)
{
	ReadReference<WahWahProxy> effect(eff);
	setEffect(effect->getEffect());
}

void AuxiliaryEffectProxy::setFilter(LowpassFilterReference flt)
{
	ReadReference<LowpassFilterProxy> filter(flt);
	setFilter(filter->getFilter());
}
void AuxiliaryEffectProxy::setFilter(HighpassFilterReference flt)
{
	ReadReference<HighpassFilterProxy> filter(flt);
	setFilter(filter->getFilter());
}
void AuxiliaryEffectProxy::setFilter(BandpassFilterReference flt)
{
	ReadReference<BandpassFilterProxy> filter(flt);
	setFilter(filter->getFilter());
}

AuxiliaryEffectReference AuxiliaryEffectManager::query(const AuxiliaryEffectProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	AuxiliaryEffectReference ref;
	if(it == buffmp.end())
	{
		ref = AuxiliaryEffectReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
AuxiliaryEffectReference AuxiliaryEffectManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	AuxiliaryEffectReference ref;
	if(it == buffmp.end())
	{
		ref = AuxiliaryEffectReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
AuxiliaryEffectReference AuxiliaryEffectManager::commit(const AuxiliaryEffectProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<AuxiliaryEffectProxy> &prxy = *ref;
			prxy.beginSet();
			prxy->changedProperties = proxy.changedProperties;
			prxy->properties = proxy.properties;
			prxy->commitData();
			prxy->queryData();
			prxy.endSet();
		});
		return ref;
	}
	pushCommand( [proxy, ref ](pGameSystem sys) {
	(void)(sys);
	Storage<AuxiliaryEffectProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effectSlot = Audio::AuxiliaryEffectSlot::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
