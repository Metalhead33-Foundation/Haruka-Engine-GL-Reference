#include "EchoProxy.hpp"
#include <cstring>

void EchoProxy::queryData()
{
	if(effect)
	{
		properties.damping = effect->getDamping();
		changedProperties.damping = false;
		properties.delay = effect->getDelay();
		changedProperties.delay = false;
		properties.feedback = effect->getFeedback();
		changedProperties.feedback = false;
		properties.lDelay = effect->getLRDelay();
		changedProperties.lDelay = false;
		properties.spread = effect->getSpread();
		changedProperties.spread = false;
	}
}
void EchoProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.damping)
		{
			effect->setDamping(properties.damping);
			changedProperties.damping = false;
		}
		if(changedProperties.delay)
		{
			effect->setDelay(properties.delay);
			changedProperties.delay = false;
		}
		if(changedProperties.feedback)
		{
			effect->setFeedback(properties.feedback);
			changedProperties.feedback = false;
		}
		if(changedProperties.lDelay)
		{
			effect->setLRDelay(properties.lDelay);
			changedProperties.lDelay = false;
		}
		if(changedProperties.spread)
		{
			effect->setSpread(properties.spread);
			changedProperties.spread = false;
		}
	}
}
EchoProxy::EchoProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
EchoProxy::EchoProxy(const EchoProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
EchoProxy::EchoProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sEchoEffect EchoProxy::getEffect() const
{
	return effect;
}

void EchoProxy::setDelay(const STime& rate)
{
	properties.delay = rate;
	changedProperties.delay = true;
}
const STime &EchoProxy::getDelay(void) const
{
	return properties.delay;
}
void EchoProxy::setLRDelay(const STime& rate)
{
	properties.lDelay = rate;
	changedProperties.lDelay = true;
}
const STime &EchoProxy::getLRDelay(void) const
{
	return properties.lDelay;
}
void EchoProxy::setDamping(float damping)
{
	properties.damping = damping;
	changedProperties.damping = true;
}
float EchoProxy::getDamping(void) const
{
	return properties.damping;
}
void EchoProxy::setFeedback(float feedback)
{
	properties.feedback = feedback;
	changedProperties.feedback = true;
}
float EchoProxy::getFeedback(void) const
{
	return properties.feedback;
}
void EchoProxy::setSpread(float spread)
{
	properties.spread = spread;
	changedProperties.spread = true;
}
float EchoProxy::getSpread(void) const
{
	return properties.spread;
}

EchoReference EchoManager::query(const EchoProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	EchoReference ref;
	if(it == buffmp.end())
	{
		ref = EchoReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
EchoReference EchoManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	EchoReference ref;
	if(it == buffmp.end())
	{
		ref = EchoReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
EchoReference EchoManager::commit(const EchoProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<EchoProxy> &prxy = *ref;
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
	Storage<EchoProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::EchoEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
