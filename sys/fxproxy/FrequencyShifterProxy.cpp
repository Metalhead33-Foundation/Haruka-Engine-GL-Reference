#include "FrequencyShifterProxy.hpp"
#include <cstring>
void FrequencyShifterProxy::queryData()
{
	if(effect)
	{
		properties.frequency = effect->getFrequency();
		changedProperties.frequency = false;
		properties.leftDirection = effect->getLeftDirection();
		changedProperties.leftDirection = false;
		properties.rightDirection = effect->getRightDirection();
		changedProperties.rightDirection = false;
	}
}
void FrequencyShifterProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.frequency)
		{
			effect->setFrequency(properties.frequency);
			changedProperties.frequency = false;
		}
		if(changedProperties.leftDirection)
		{
			effect->setLeftDirection(properties.leftDirection);
			changedProperties.leftDirection = false;
		}
		if(changedProperties.rightDirection)
		{
			effect->setRightDirection(properties.rightDirection);
			changedProperties.rightDirection = false;
		}
	}
}
FrequencyShifterProxy::FrequencyShifterProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
FrequencyShifterProxy::FrequencyShifterProxy(const FrequencyShifterProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
FrequencyShifterProxy::FrequencyShifterProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sFrequencyShifterEffect FrequencyShifterProxy::getEffect() const
{
	return effect;
}

void FrequencyShifterProxy::setFrequency(float frequency)
{
	properties.frequency = frequency;
	changedProperties.frequency = true;
}
float FrequencyShifterProxy::getFrequency(void) const
{
	return properties.frequency;
}
void FrequencyShifterProxy::setLeftDirection(int leftDirection)
{
	properties.leftDirection = leftDirection;
	changedProperties.leftDirection = true;
}
int FrequencyShifterProxy::getLeftDirection(void) const
{
	return properties.leftDirection;
}
void FrequencyShifterProxy::setRightDirection(int rightDirection)
{
	properties.rightDirection = rightDirection;
	changedProperties.rightDirection = true;
}
int FrequencyShifterProxy::getRightDirection(void) const
{
	return properties.rightDirection;
}
FrequencyShifterReference FrequencyShifterManager::query(const FrequencyShifterProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	FrequencyShifterReference ref;
	if(it == buffmp.end())
	{
		ref = FrequencyShifterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
FrequencyShifterReference FrequencyShifterManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	FrequencyShifterReference ref;
	if(it == buffmp.end())
	{
		ref = FrequencyShifterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
FrequencyShifterReference FrequencyShifterManager::commit(const FrequencyShifterProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<FrequencyShifterProxy> &prxy = *ref;
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
	Storage<FrequencyShifterProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::FrequencyShifterEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
