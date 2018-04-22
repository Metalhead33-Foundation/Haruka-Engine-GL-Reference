#include "LowpassFilterProxy.hpp"
#include <cstring>

void LowpassFilterProxy::queryData()
{
	if(filter)
	{
		properties.gain = filter->getGain();
		changedProperties.gain = false;
		properties.highFrequencyGain = filter->getHighFrequencyGain();
		changedProperties.highFrequencyGain = false;
	}
}
void LowpassFilterProxy::commitData()
{
	if(filter)
	{
		if(changedProperties.gain)
		{
			filter->setGain(properties.gain);
			changedProperties.gain = false;
		}
		if(changedProperties.highFrequencyGain)
		{
			filter->setHighFrequencyGain(properties.highFrequencyGain);
			changedProperties.highFrequencyGain = false;
		}
	}
}
const Audio::sLowpassFilter LowpassFilterProxy::getFilter() const
{
	return filter;
}

void LowpassFilterProxy::setGain(float gain)
{
	properties.gain = gain;
	changedProperties.gain = true;
}
float LowpassFilterProxy::getGain() const
{
	return properties.gain;
}
void LowpassFilterProxy::setHighFrequencyGain(float gain)
{
	properties.highFrequencyGain = gain;
	changedProperties.highFrequencyGain = true;
}
float LowpassFilterProxy::getHighFrequencyGain() const
{
	return properties.highFrequencyGain;
}

LowpassFilterProxy::LowpassFilterProxy()
	: Proxy(""), filter(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
LowpassFilterProxy::LowpassFilterProxy(const LowpassFilterProxy& cpy)
	: Proxy(cpy.Id), filter(cpy.filter)
{
	this->properties = cpy.properties;
	this->changedProperties = cpy.changedProperties;
}
LowpassFilterProxy::LowpassFilterProxy(const std::string& id)
	: Proxy(id), filter(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}

LowpassFilterReference LowpassFilterManager::query(const LowpassFilterProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	LowpassFilterReference ref;
	if(it == buffmp.end())
	{
		ref = LowpassFilterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
LowpassFilterReference LowpassFilterManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	LowpassFilterReference ref;
	if(it == buffmp.end())
	{
		ref = LowpassFilterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
LowpassFilterReference LowpassFilterManager::commit(const LowpassFilterProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<LowpassFilterProxy> &prxy = *ref;
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
	Storage<LowpassFilterProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->filter = Audio::LowpassFilter::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
