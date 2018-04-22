#include "ProxyAudioSource.hpp"
#include <cstring>

SourceReference SourceManager::query(const SourceProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	SourceReference ref;
	if(it == buffmp.end())
	{
		ref = SourceReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
SourceReference SourceManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	SourceReference ref;
	if(it == buffmp.end())
	{
		ref = SourceReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
AuxiliaryEffectReference SourceManager::commit(const SourceProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<SourceProxy> &prxy = *ref;
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
	Storage<SourceProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effectSlot = Audio::AuxiliaryEffectSlot::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
