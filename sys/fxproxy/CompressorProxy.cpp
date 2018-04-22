#include "CompressorProxy.hpp"
#include <cstring>

void CompressorProxy::queryData()
{
	if(effect)
	{
		properties.isOn = effect->isOn();
		changedProperties.isOn = false;
	}
}
void CompressorProxy::commitData()
{
	if(effect)
	{
		if(properties.isOn) effect->turnOn();
		else effect->turnOff();
		changedProperties.isOn = false;
	}
}
CompressorProxy::CompressorProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
CompressorProxy::CompressorProxy(const CompressorProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
CompressorProxy::CompressorProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sCompressorEffect CompressorProxy::getEffect() const
{
	return effect;
}

void CompressorProxy::turnOn()
{
	if(!properties.isOn)
	{
		properties.isOn = true;
		changedProperties.isOn = true;
	}
}
void CompressorProxy::turnOff()
{
	if(properties.isOn)
	{
		properties.isOn = false;
		changedProperties.isOn = true;
	}
}
bool CompressorProxy::isOn() const
{
	return properties.isOn;
}

CompressorReference CompressorManager::query(const CompressorProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	CompressorReference ref;
	if(it == buffmp.end())
	{
		ref = CompressorReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
CompressorReference CompressorManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	CompressorReference ref;
	if(it == buffmp.end())
	{
		ref = CompressorReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
CompressorReference CompressorManager::commit(const CompressorProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<CompressorProxy> &prxy = *ref;
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
	Storage<CompressorProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::CompressorEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
