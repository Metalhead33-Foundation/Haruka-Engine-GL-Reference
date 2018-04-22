#include "HighpassFilterProxy.hpp"
#include <cstring>

void HighpassFilterProxy::queryData()
{
	if(filter)
	{
		properties.gain = filter->getGain();
		changedProperties.gain = false;
		properties.lowFrequencyGain = filter->getLowFrequencyGain();
		changedProperties.lowFrequencyGain = false;
	}
}
void HighpassFilterProxy::commitData()
{
	if(filter)
	{
		if(changedProperties.gain)
		{
			filter->setGain(properties.gain);
			changedProperties.gain = false;
		}
		if(changedProperties.lowFrequencyGain)
		{
			filter->setLowFrequencyGain(properties.lowFrequencyGain);
			changedProperties.lowFrequencyGain = false;
		}
	}
}
const Audio::sHighpassFilter HighpassFilterProxy::getFilter() const
{
	return filter;
}

void HighpassFilterProxy::setGain(float gain)
{
	properties.gain = gain;
	changedProperties.gain = true;
}
float HighpassFilterProxy::getGain() const
{
	return properties.gain;
}
void HighpassFilterProxy::setLowFrequencyGain(float gain)
{
	properties.lowFrequencyGain = gain;
	changedProperties.lowFrequencyGain = true;
}
float HighpassFilterProxy::getLowFrequencyGain() const
{
	return properties.lowFrequencyGain;
}

HighpassFilterProxy::HighpassFilterProxy()
	: Proxy(""), filter(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
HighpassFilterProxy::HighpassFilterProxy(const HighpassFilterProxy& cpy)
	: Proxy(cpy.Id), filter(cpy.filter)
{
	this->properties = cpy.properties;
	this->changedProperties = cpy.changedProperties;
}
HighpassFilterProxy::HighpassFilterProxy(const std::string& id)
	: Proxy(id), filter(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}

HighpassFilterReference HighpassFilterManager::query(const HighpassFilterProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	HighpassFilterReference ref;
	if(it == buffmp.end())
	{
		ref = HighpassFilterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
HighpassFilterReference HighpassFilterManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	HighpassFilterReference ref;
	if(it == buffmp.end())
	{
		ref = HighpassFilterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
HighpassFilterReference HighpassFilterManager::commit(const HighpassFilterProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<HighpassFilterProxy> &prxy = *ref;
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
	Storage<HighpassFilterProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->filter = Audio::HighpassFilter::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
