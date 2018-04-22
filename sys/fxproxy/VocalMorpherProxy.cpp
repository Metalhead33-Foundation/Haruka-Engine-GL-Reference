#include "VocalMorpherProxy.hpp"
#include <cstring>

void VocalMorpherProxy::queryData()
{
	if(effect)
	{
		properties.waveform = effect->getWaveform();
		changedProperties.waveform = false;
		properties.coarseTuneA = effect->getCoarseTuneA();
		changedProperties.coarseTuneA = false;
		properties.coarseTuneB = effect->getCoarseTuneB();
		changedProperties.coarseTuneB = false;
		properties.morpherRate = effect->getMorpherRate();
		changedProperties.morpherRate = false;
		properties.phonemeA = effect->getPhonemeA();
		changedProperties.phonemeA = false;
		properties.phonemeB = effect->getPhonemeB();
		changedProperties.phonemeB = false;
	}
}
void VocalMorpherProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.waveform)
		{
			effect->setWaveform(properties.waveform);
			changedProperties.waveform = false;
		}
		if(changedProperties.coarseTuneA)
		{
			effect->setCoarseTuneA(properties.coarseTuneA);
			changedProperties.coarseTuneA = false;
		}
		if(changedProperties.coarseTuneB)
		{
			effect->setCoarseTuneB(properties.coarseTuneB);
			changedProperties.coarseTuneB = false;
		}
		if(changedProperties.morpherRate)
		{
			effect->setMorpherRate(properties.morpherRate);
			changedProperties.morpherRate = false;
		}
		if(changedProperties.phonemeA)
		{
			effect->setPhonemeA(properties.phonemeA);
			changedProperties.phonemeA = false;
		}
		if(changedProperties.phonemeB)
		{
			effect->setPhonemeB(properties.phonemeB);
			changedProperties.phonemeB = false;
		}
	}
}
const Audio::sVocalMorpherEffect VocalMorpherProxy::getEffect() const
{
	return effect;
}

VocalMorpherProxy::VocalMorpherProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
VocalMorpherProxy::VocalMorpherProxy(const VocalMorpherProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
VocalMorpherProxy::VocalMorpherProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
void VocalMorpherProxy::setWaveform(Waveform waveform)
{
	properties.waveform = waveform;
	changedProperties.waveform = true;
}
VocalMorpherProxy::Waveform VocalMorpherProxy::getWaveform(void) const
{
	return properties.waveform;
}

void VocalMorpherProxy::setPhonemeA(char phonemeA)
{
	properties.phonemeA = phonemeA;
	changedProperties.phonemeA = true;
}
void VocalMorpherProxy::setPhonemeB(char phonemeB)
{
	properties.phonemeB = phonemeB;
	changedProperties.phonemeB = true;
}
void VocalMorpherProxy::setCoarseTuneA(char coarseTuneA)
{
	properties.coarseTuneA = coarseTuneA;
	changedProperties.coarseTuneA = true;
}
void VocalMorpherProxy::setCoarseTuneB(char coarseTuneB)
{
	properties.coarseTuneB = coarseTuneB;
	changedProperties.coarseTuneB = true;
}
void VocalMorpherProxy::setMorpherRate(float morpherRate)
{
	properties.morpherRate = morpherRate;
	changedProperties.morpherRate = true;
}

char VocalMorpherProxy::getPhonemeA(void) const
{
	return properties.phonemeA;
}
char VocalMorpherProxy::getPhonemeB(void) const
{
	return properties.phonemeB;
}
char VocalMorpherProxy::getCoarseTuneA(void) const
{
	return properties.coarseTuneA;
}
char VocalMorpherProxy::getCoarseTuneB(void) const
{
	return properties.coarseTuneB;
}
float VocalMorpherProxy::getMorpherRate(void) const
{
	return properties.morpherRate;
}

VocalMorpherReference VocalMorpherManager::query(const VocalMorpherProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	VocalMorpherReference ref;
	if(it == buffmp.end())
	{
		ref = VocalMorpherReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
VocalMorpherReference VocalMorpherManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	VocalMorpherReference ref;
	if(it == buffmp.end())
	{
		ref = VocalMorpherReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
VocalMorpherReference VocalMorpherManager::commit(const VocalMorpherProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<VocalMorpherProxy> &prxy = *ref;
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
	Storage<VocalMorpherProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::VocalMorpherEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
