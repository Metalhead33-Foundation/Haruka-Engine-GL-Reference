#include "BandpassFilterProxy.hpp"
#include <cstring>

void BandpassFilterProxy::queryData()
{
	if(filter)
	{
		properties.gain = filter->getGain();
		changedProperties.gain = false;
		properties.highFrequencyGain = filter->getHighFrequencyGain();
		changedProperties.highFrequencyGain = false;
		properties.lowFrequencyGain = filter->getLowFrequencyGain();
		changedProperties.lowFrequencyGain = false;
	}
}
void BandpassFilterProxy::commitData()
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
		if(changedProperties.lowFrequencyGain)
		{
			filter->setLowFrequencyGain(properties.lowFrequencyGain);
			changedProperties.lowFrequencyGain = false;
		}
	}
}
const Audio::sBandpassFilter BandpassFilterProxy::getFilter() const
{
	return filter;
}

void BandpassFilterProxy::setGain(float gain)
{
	properties.gain = gain;
	changedProperties.gain = true;
}
float BandpassFilterProxy::getGain() const
{
	return properties.gain;
}
void BandpassFilterProxy::setHighFrequencyGain(float gain)
{
	properties.highFrequencyGain = gain;
	changedProperties.highFrequencyGain = true;
}
float BandpassFilterProxy::getHighFrequencyGain() const
{
	return properties.highFrequencyGain;
}
void BandpassFilterProxy::setLowFrequencyGain(float gain)
{
	properties.lowFrequencyGain = gain;
	changedProperties.lowFrequencyGain = true;
}
float BandpassFilterProxy::getLowFrequencyGain() const
{
	return properties.lowFrequencyGain;
}

BandpassFilterProxy::BandpassFilterProxy()
	: Proxy(""), filter(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
BandpassFilterProxy::BandpassFilterProxy(const BandpassFilterProxy& cpy)
	: Proxy(cpy.Id), filter(cpy.filter)
{
	this->properties = cpy.properties;
	this->changedProperties = cpy.changedProperties;
}
BandpassFilterProxy::BandpassFilterProxy(const std::string& id)
	: Proxy(id), filter(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}

BandpassFilterReference BandpassFilterManager::query(const BandpassFilterProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	BandpassFilterReference ref;
	if(it == buffmp.end())
	{
		ref = BandpassFilterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
BandpassFilterReference BandpassFilterManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	BandpassFilterReference ref;
	if(it == buffmp.end())
	{
		ref = BandpassFilterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
BandpassFilterReference BandpassFilterManager::commit(const BandpassFilterProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<BandpassFilterProxy> &prxy = *ref;
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
	Storage<BandpassFilterProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->filter = Audio::BandpassFilter::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
