#include "DistortionProxy.hpp"
#include <cstring>

void DistortionProxy::queryData()
{
	if(effect)
	{
		properties.eQBandwith = effect->getEQBandwith();
		changedProperties.eQBandwith = false;
		properties.eQCenter = effect->getEQBandwith();
		changedProperties.eQCenter = false;
		properties.edge = effect->getEdge();
		changedProperties.edge = false;
		properties.gain = effect->getGain();
		changedProperties.gain = false;
		properties.lowPassCutoff = effect->getLowPassCutoff();
		changedProperties.lowPassCutoff = false;
	}
}
void DistortionProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.eQBandwith)
		{
			effect->setEQBandwith(properties.eQBandwith);
			changedProperties.eQBandwith = false;
		}
		if(changedProperties.eQCenter)
		{
			effect->setEQCenter(properties.eQCenter);
			changedProperties.eQCenter = false;
		}
		if(changedProperties.edge)
		{
			effect->setEdge(properties.edge);
			changedProperties.edge = false;
		}
		if(changedProperties.gain)
		{
			effect->setGain(properties.gain);
			changedProperties.gain = false;
		}
		if(changedProperties.lowPassCutoff)
		{
			effect->setLowPassCutoff(properties.lowPassCutoff);
			changedProperties.lowPassCutoff = false;
		}
	}
}
DistortionProxy::DistortionProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
DistortionProxy::DistortionProxy(const DistortionProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
DistortionProxy::DistortionProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sDistortionEffect DistortionProxy::getEffect() const
{
	return effect;
}

void DistortionProxy::setEdge(float edge)
{
	properties.edge = edge;
	changedProperties.edge = true;
}
float DistortionProxy::getEdge(void) const
{
	return properties.edge;
}
void DistortionProxy::setGain(float gain)
{
	properties.gain = gain;
	changedProperties.gain = true;
}
float DistortionProxy::getGain(void) const
{
	return properties.gain;
}
void DistortionProxy::setLowPassCutoff(float gain)
{
	properties.lowPassCutoff = gain;
	changedProperties.lowPassCutoff = true;
}
float DistortionProxy::getLowPassCutoff(void) const
{
	return properties.lowPassCutoff;
}
void DistortionProxy::setEQCenter(float gain)
{
	properties.eQCenter = gain;
	changedProperties.eQCenter = true;
}
float DistortionProxy::getEQCenter(void) const
{
	return properties.eQCenter;
}
void DistortionProxy::setEQBandwith(float gain)
{
	properties.eQBandwith = gain;
	changedProperties.eQBandwith = true;
}
float DistortionProxy::getEQBandwith(void) const
{
	return properties.eQBandwith;
}

DistortionReference DistortionManager::query(const DistortionProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	DistortionReference ref;
	if(it == buffmp.end())
	{
		ref = DistortionReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
DistortionReference DistortionManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	DistortionReference ref;
	if(it == buffmp.end())
	{
		ref = DistortionReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
DistortionReference DistortionManager::commit(const DistortionProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<DistortionProxy> &prxy = *ref;
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
	Storage<DistortionProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::DistortionEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
