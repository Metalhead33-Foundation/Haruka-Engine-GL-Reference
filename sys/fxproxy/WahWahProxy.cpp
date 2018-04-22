#include "WahWahProxy.hpp"
#include <cstring>


void WahWahProxy::queryData()
{
	if(effect)
	{
		properties.attackTime = effect->getAttackTime();
		changedProperties.attackTime = false;
		properties.peakGain = effect->getPeakGain();
		changedProperties.peakGain = false;
		properties.releaseTime = effect->getReleaseTime();
		changedProperties.releaseTime = false;
		properties.resonance = effect->getResonance();
		changedProperties.resonance = false;
	}
}
void WahWahProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.attackTime)
		{
			effect->setAttackTime(properties.attackTime);
			changedProperties.attackTime = false;
		}
		if(changedProperties.peakGain)
		{
			effect->setPeakGain(properties.peakGain);
			changedProperties.peakGain = false;
		}
		if(changedProperties.releaseTime)
		{
			effect->setReleaseTime(properties.releaseTime);
			changedProperties.releaseTime = false;
		}
		if(changedProperties.resonance)
		{
			effect->setResonance(properties.resonance);
			changedProperties.resonance = false;
		}
	}
}
WahWahProxy::WahWahProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
WahWahProxy::WahWahProxy(const WahWahProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
WahWahProxy::WahWahProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sWahWahEffect WahWahProxy::getEffect() const
{
	return effect;
}
void WahWahProxy::setAttackTime(const STime& time)
{
	properties.attackTime = time;
	changedProperties.attackTime = true;
}
const STime& WahWahProxy::getAttackTime(void) const
{
	return properties.attackTime;
}
void WahWahProxy::setReleaseTime(const STime& time)
{
	properties.releaseTime = time;
	changedProperties.releaseTime = true;
}
const STime& WahWahProxy::getReleaseTime(void) const
{
	return properties.releaseTime;
}
void WahWahProxy::setResonance(float resonance)
{
	properties.resonance = resonance;
	changedProperties.resonance = true;
}
float WahWahProxy::getResonance(void) const
{
	return properties.resonance;
}
void WahWahProxy::setPeakGain(float peakGain)
{
	properties.peakGain = peakGain;
	changedProperties.peakGain = true;
}
float WahWahProxy::getPeakGain(void) const
{
	return properties.peakGain;
}

WahWahReference WahWahManager::query(const WahWahProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	WahWahReference ref;
	if(it == buffmp.end())
	{
		ref = WahWahReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
WahWahReference WahWahManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	WahWahReference ref;
	if(it == buffmp.end())
	{
		ref = WahWahReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
WahWahReference WahWahManager::commit(const WahWahProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<WahWahProxy> &prxy = *ref;
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
	Storage<WahWahProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::WahWahEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
