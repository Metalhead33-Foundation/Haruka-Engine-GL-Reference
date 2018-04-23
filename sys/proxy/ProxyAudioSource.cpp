#include "ProxyAudioSource.hpp"
#include <cstring>

void SourceProxy::queryData();
void SourceProxy::commitData();
SourceProxy::SourceProxy();
SourceProxy::SourceProxy(const SourceProxy& cpy);
SourceProxy::SourceProxy(const std::string& id);
const Audio::sAudioSource SourceProxy::getSource() const
{
	return source;
}

/* Setters */
void SourceProxy::setPitch(float pitch);
void SourceProxy::setGain(float gain);
void SourceProxy::setPosition(float x, float y, float z);
void SourceProxy::setPosition(const glm::vec3& pos);
void SourceProxy::setRelativity(bool shouldBeRelative);
void SourceProxy::setMinimumDistance(float minDist);
void SourceProxy::setAttenuation(float attenuation);
void SourceProxy::setLooping(bool looping);
void SourceProxy::setFilter(Audio::sFilter nfilter);
void SourceProxy::setAuxiliaryEffectSlot(Audio::sAuxiliaryEffectSlot aux);
void SourceProxy::setLoadPath(const std::string& loadpath);
void SourceProxy::setBuffer(Audio::sBuffer buff);

/* Getters */
float SourceProxy::getPitch(void) const;
float SourceProxy::getGain(void) const;
const glm::vec3& SourceProxy::getPosition(void) const;
bool SourceProxy::getRelativity(void) const;
float SourceProxy::getMinimumDistance(void) const;
float SourceProxy::getAttenuation(void) const;
ALint SourceProxy::getStatus(void) const;
bool SourceProxygetLooping(void) const;
const sFilter SourceProxy::getFilter() const;
const sAuxiliaryEffectSlot SourceProxy::getAuxiliaryEffectSlot() const;
const std::string& SourceProxy::getLoadPath() const;
const Audio::sBuffer SourceProxy::getBuffer() const;

/* Actually used functions */
void SourceProxy::setAuxiliaryEffectSlot(AuxiliaryEffectReference aux);
void SourceProxy::setFilter(LowpassFilterReference flt);
void SourceProxy::setFilter(HighpassFilterReference flt);
void SourceProxy::setFilter(BandpassFilterReference flt);
void SourceProxy::setBuffer(BufferReference buff);

void SourceProxy::play()
{
	if(source) source->play();
}
void SourceProxy::pause()
{
	if(source) source->pause();
}
void SourceProxy::stop()
{
	if(source) source->stop();
}

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
