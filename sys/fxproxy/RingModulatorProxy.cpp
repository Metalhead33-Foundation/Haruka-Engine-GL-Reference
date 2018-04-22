#include "RingModulatorProxy.hpp"
#include <cstring>

void RingModulatorProxy::queryData()
{
	if(effect)
	{
		properties.frequency = effect->getFrequency();
		changedProperties.frequency = false;
		properties.highpassCutoff = effect->getHighpassCutoff();
		changedProperties.highpassCutoff = false;
		properties.waveform = effect->getWaveform();
		changedProperties.waveform = false;
	}
}
void RingModulatorProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.frequency)
		{
			effect->setFrequency(properties.frequency);
			changedProperties.frequency = false;
		}
		if(changedProperties.highpassCutoff)
		{
			effect->setHighpassCutoff(properties.highpassCutoff);
			changedProperties.highpassCutoff = false;
		}
		if(changedProperties.waveform)
		{
			effect->setWaveform(properties.waveform);
			changedProperties.waveform = false;
		}
	}
}
RingModulatorProxy::RingModulatorProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
RingModulatorProxy::RingModulatorProxy(const RingModulatorProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
RingModulatorProxy::RingModulatorProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sRingModulatorEffect RingModulatorProxy::getEffect() const
{
	return effect;
}

void RingModulatorProxy::setWaveform(Waveform waveform)
{
	properties.waveform = waveform;
	changedProperties.waveform = true;
}
RingModulatorProxy::Waveform RingModulatorProxy::getWaveform(void) const
{
	return properties.waveform;
}

void RingModulatorProxy::setFrequency(float frequency)
{
	properties.frequency = frequency;
	changedProperties.frequency = true;
}
float RingModulatorProxy::getFrequency(void) const
{
	return properties.frequency;
}
void RingModulatorProxy::setHighpassCutoff(float highpassCutoff)
{
	properties.highpassCutoff = highpassCutoff;
	changedProperties.highpassCutoff = true;
}
float RingModulatorProxy::getHighpassCutoff(void) const
{
	return properties.highpassCutoff;
}

RingModulatorReference RingModulatorManager::query(const RingModulatorProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	RingModulatorReference ref;
	if(it == buffmp.end())
	{
		ref = RingModulatorReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
RingModulatorReference RingModulatorManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	RingModulatorReference ref;
	if(it == buffmp.end())
	{
		ref = RingModulatorReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
RingModulatorReference RingModulatorManager::commit(const RingModulatorProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<RingModulatorProxy> &prxy = *ref;
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
	Storage<RingModulatorProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::RingModulatorEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
