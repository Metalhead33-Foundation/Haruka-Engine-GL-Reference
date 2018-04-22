#include "EqualizerProxy.hpp"
#include <cstring>

void EqualizerProxy::queryData()
{
	if(effect)
	{
		properties.lowCutoff = effect->getLowCutoff();
		changedProperties.lowCutoff = false;
		properties.lowGain = effect->getLowGain();
		changedProperties.lowGain = false;
		properties.highCutoff = effect->getHighCutoff();
		changedProperties.highCutoff = false;
		properties.highGain = effect->getHighGain();
		changedProperties.highGain = false;
		properties.mid1Center = effect->getMid1Center();
		changedProperties.mid1Center = false;
		properties.mid1Gain = effect->getMid1Gain();
		changedProperties.mid1Gain = false;
		properties.mid1Width = effect->getMid1Width();
		changedProperties.mid1Width = false;
		properties.mid2Center = effect->getMid2Center();
		changedProperties.mid2Center = false;
		properties.mid2Gain = effect->getMid2Gain();
		changedProperties.mid2Gain = false;
		properties.mid2Width = effect->getMid2Width();
		changedProperties.mid2Width = false;
	}
}
void EqualizerProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.lowCutoff) {
			effect->setLowCutoff(properties.lowCutoff);
			changedProperties.lowCutoff = false;
		}
		if(changedProperties.lowGain) {
			effect->setLowGain(properties.lowGain);
			changedProperties.lowGain = false;
		}
		if(changedProperties.highCutoff) {
			effect->setHighCutoff(properties.highCutoff);
			changedProperties.highCutoff = false;
		}
		if(changedProperties.highGain) {
			effect->setHighGain(properties.highGain);
			changedProperties.highGain = false;
		}
		if(changedProperties.mid1Center) {
			effect->setMid1Center(properties.mid1Center);
			changedProperties.mid1Center = false;
		}
		if(changedProperties.mid1Gain) {
			effect->setMid1Gain(properties.mid1Gain);
			changedProperties.mid1Gain = false;
		}
		if(changedProperties.mid1Width) {
			effect->setMid1Width(properties.mid1Width);
			changedProperties.mid1Width = false;
		}
		if(changedProperties.mid2Center) {
			effect->setMid2Center(properties.mid2Center);
			changedProperties.mid2Center = false;
		}
		if(changedProperties.mid2Gain) {
			effect->setMid2Gain(properties.mid2Gain);
			changedProperties.mid2Gain = false;
		}
		if(changedProperties.mid2Width) {
			effect->setMid2Center(properties.mid2Width);
			changedProperties.mid2Width = false;
		}
	}
}
EqualizerProxy::EqualizerProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
EqualizerProxy::EqualizerProxy(const EqualizerProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
EqualizerProxy::EqualizerProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sEqualizerEffect EqualizerProxy::getEffect() const
{
	return effect;
}

void EqualizerProxy::setLowGain(float lowGain)
{
	properties.lowGain = lowGain;
	changedProperties.lowGain = true;
}
void EqualizerProxy::setLowCutoff(float lowCutoff)
{
	properties.lowCutoff = lowCutoff;
	changedProperties.lowCutoff = true;
}
void EqualizerProxy::setMid1Gain(float mid1Gain)
{
	properties.mid1Gain = mid1Gain;
	changedProperties.mid1Gain = true;
}
void EqualizerProxy::setMid1Center(float mid1Center)
{
	properties.mid1Center = mid1Center;
	changedProperties.mid1Center = true;
}
void EqualizerProxy::setMid1Width(float mid1Width)
{
	properties.mid1Width = mid1Width;
	changedProperties.mid1Width = true;
}
void EqualizerProxy::setMid2Gain(float mid1Gain)
{
	properties.mid2Gain = mid1Gain;
	changedProperties.mid2Gain = true;
}
void EqualizerProxy::setMid2Center(float mid1Center)
{
	properties.mid2Center = mid1Center;
	changedProperties.mid2Center = true;
}
void EqualizerProxy::setMid2Width(float mid1Width)
{
	properties.mid2Width = mid1Width;
	changedProperties.mid2Width = true;
}
void EqualizerProxy::setHighGain(float highGain)
{
	properties.highGain = highGain;
	changedProperties.highGain = true;
}
void EqualizerProxy::setHighCutoff(float highCutoff)
{
	properties.highCutoff = highCutoff;
	changedProperties.highCutoff = true;
}

float EqualizerProxy::getLowGain(void) const
{
	return properties.lowGain;
}
float EqualizerProxy::getLowCutoff(void) const
{
	return properties.lowCutoff;
}
float EqualizerProxy::getMid1Gain(void) const
{
	return properties.mid1Gain;
}
float EqualizerProxy::getMid1Center(void) const
{
	return properties.mid1Center;
}
float EqualizerProxy::getMid1Width(void) const
{
	return properties.mid1Width;
}
float EqualizerProxy::getMid2Gain(void) const
{
	return properties.mid2Gain;
}
float EqualizerProxy::getMid2Center(void) const
{
	return properties.mid2Center;
}
float EqualizerProxy::getMid2Width(void) const
{
	return properties.mid2Width;
}
float EqualizerProxy::getHighGain(void) const
{
	return properties.highGain;
}
float EqualizerProxy::getHighCutoff(void) const
{
	return properties.highCutoff;
}

EqualizerReference EqualizerManager::query(const EqualizerProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	EqualizerReference ref;
	if(it == buffmp.end())
	{
		ref = EqualizerReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
EqualizerReference EqualizerManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	EqualizerReference ref;
	if(it == buffmp.end())
	{
		ref = EqualizerReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
EqualizerReference EqualizerManager::commit(const EqualizerProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<EqualizerProxy> &prxy = *ref;
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
	Storage<EqualizerProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::EqualizerEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
