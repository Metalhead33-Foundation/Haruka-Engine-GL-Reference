#include "ProxyAudioSource.hpp"
#include <cstring>

void SourceManager::queryData();
void SourceManager::commitData();
SourceManager::SourceProxy();
SourceManager::SourceProxy(const SourceProxy& cpy);
SourceManager::SourceProxy(const std::string& id);
const Audio::sAudioSource SourceManager::getSource() const;

/* Setters */
void SourceManager::setPitch(float pitch);
void SourceManager::setGain(float gain);
void SourceManager::setPosition(float x, float y, float z);
void SourceManager::setPosition(const glm::vec3& pos);
void SourceManager::setRelativity(bool shouldBeRelative);
void SourceManager::setMinimumDistance(float minDist);
void SourceManager::setAttenuation(float attenuation);
void SourceManager::setLooping(bool looping);
void SourceManager::setFilter(Audio::sFilter nfilter);
void SourceManager::setAuxiliaryEffectSlot(Audio::sAuxiliaryEffectSlot aux);
void SourceManager::setLoadPath(const std::string& loadpath);
void SourceManager::setBuffer(Audio::sBuffer buff);

/* Getters */
float SourceManager::getPitch(void) const;
float SourceManager::getGain(void) const;
const glm::vec3& SourceManager::getPosition(void) const;
bool SourceManager::getRelativity(void) const;
float SourceManager::getMinimumDistance(void) const;
float SourceManager::getAttenuation(void) const;
ALint SourceManager::getStatus(void) const;
boolSourceManager:: getLooping(void) const;
const sFilter SourceManager::getFilter() const;
const sAuxiliaryEffectSlot SourceManager::getAuxiliaryEffectSlot() const;
const std::string& SourceManager::getLoadPath() const;
const Audio::sBuffer SourceManager::getBuffer() const;

/* Actually used functions */
void SourceManager::setAuxiliaryEffectSlot(AuxiliaryEffectReference aux);
void SourceManager::setFilter(LowpassFilterReference flt);
void SourceManager::setFilter(HighpassFilterReference flt);
void SourceManager::setFilter(BandpassFilterReference flt);
void SourceManager::setBuffer(BufferReference buff);

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
