#include "PitchShifterProxy.hpp"
#include <cstring>


void PitchShifterProxy::queryData()
{
	if(effect)
	{
		properties.coarseTune = effect->getCoarseTune();
		changedProperties.coarseTune = false;
		properties.fineTune = effect->getFineTune();
		changedProperties.fineTune = false;
	}
}
void PitchShifterProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.coarseTune)
		{
			effect->setCoarseTune(properties.coarseTune);
			changedProperties.coarseTune = false;
		}
		if(changedProperties.fineTune)
		{
			effect->setFineTune(properties.fineTune);
			changedProperties.fineTune = false;
		}
	}
}
PitchShifterProxy::PitchShifterProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
PitchShifterProxy::PitchShifterProxy(const PitchShifterProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
PitchShifterProxy::PitchShifterProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sPitchShifterEffect PitchShifterProxy::getEffect() const
{
	return effect;
}

void PitchShifterProxy::setCoarseTune(int courseTune)
{
	properties.coarseTune = courseTune;
	changedProperties.coarseTune = true;
}
int PitchShifterProxy::getCoarseTune(void) const
{
	return  properties.coarseTune;
}
void PitchShifterProxy::setFineTune(int fineTune)
{
	properties.fineTune = fineTune;
	changedProperties.fineTune = true;
}
int PitchShifterProxy::getFineTune(void) const
{
	return properties.fineTune;
}

PitchShifterReference PitchShifterManager::query(const PitchShifterProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	PitchShifterReference ref;
	if(it == buffmp.end())
	{
		ref = PitchShifterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
PitchShifterReference PitchShifterManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	PitchShifterReference ref;
	if(it == buffmp.end())
	{
		ref = PitchShifterReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
PitchShifterReference PitchShifterManager::commit(const PitchShifterProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<PitchShifterProxy> &prxy = *ref;
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
	Storage<PitchShifterProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::PitchShifterEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
