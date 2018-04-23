#include "ProxyAudioSource.hpp"
#include "../../audio/StreamedAudio.hpp"
#include "../../audio/SoundSource.hpp"
#include "../GameSystem.hpp"
#include <cstring>

void SourceProxy::queryData()
{
	if(source)
	{
		properties.pitch = source->getPitch();
		changedProperties.pitch = false;
		properties.gain = source->getGain();
		changedProperties.gain = false;
		properties.pos = source->getPosition();
		changedProperties.pos = false;
		properties.relativity = source->getRelativity();
		changedProperties.relativity = false;
		properties.minDist = source->getMinimumDistance();
		changedProperties.minDist = false;
		properties.attenuation = source->getAttenuation();
		changedProperties.attenuation = false;
		properties.looping = source->getLooping();
		changedProperties.looping = false;
		properties.filter = source->getFilter();
		changedProperties.filter = false;
		properties.aux = source->getAuxiliaryEffectSlot();
		changedProperties.aux = false;
		if(!isStreamed) {
		Audio::SoundSource* src = dynamic_cast<Audio::SoundSource*>(source.get());
		if(src) properties.buffer = src->getBuffer();
		else properties.buffer = nullptr;
		} else properties.buffer = nullptr;
		changedProperties.buffer = false;
	}
}
void SourceProxy::commitData()
{
	if(source)
	{
		if(changedProperties.pitch)
		{
			source->setPitch(properties.pitch);
			changedProperties.pitch = false;
		}
		if(changedProperties.gain)
		{
			source->setGain(properties.gain);
			changedProperties.gain = false;
		}
		if(changedProperties.pos)
		{
			source->setPosition(properties.pos);
			changedProperties.pos = false;
		}
		if(changedProperties.relativity)
		{
			source->setRelativity(properties.relativity);
			changedProperties.relativity = false;
		}
		if(changedProperties.minDist)
		{
			source->setMinimumDistance(properties.minDist);
			changedProperties.minDist = false;
		}
		if(changedProperties.attenuation)
		{
			source->setAttenuation(properties.attenuation);
			changedProperties.attenuation = false;
		}
		if(changedProperties.looping)
		{
			source->setLooping(properties.looping);
			changedProperties.looping = false;
		}
		if(changedProperties.filter)
		{
			source->setFilter(properties.filter);
			changedProperties.filter = false;
		}
		if(changedProperties.aux)
		{
			source->setAuxiliaryEffectSlot(properties.aux);
			changedProperties.aux = false;
		}
		if(changedProperties.buffer)
		{
			if(!isStreamed) {
				Audio::SoundSource* src = dynamic_cast<Audio::SoundSource*>(source.get());
				if(src) src->setBuffer(properties.buffer);
			}
			changedProperties.buffer = false;
		}
	}
}
SourceProxy::SourceProxy()
	: Proxy(""), loadPath(""), isStreamed(false), source(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
SourceProxy::SourceProxy(const SourceProxy& cpy)
	: Proxy(cpy.Id), loadPath(cpy.loadPath), isStreamed(cpy.isStreamed), source(cpy.source)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
SourceProxy::SourceProxy(const std::string& id, bool isStreamed)
	: Proxy(id), loadPath(""), isStreamed(isStreamed), source(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
SourceProxy::SourceProxy(const std::string& id, const std::string& loadpath)
	: Proxy(id), loadPath(loadpath), isStreamed(true), source(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
SourceProxy::SourceProxy(const std::string& id, const char* loadpath)
	: Proxy(id), loadPath(loadpath), isStreamed(true), source(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
SourceProxy::SourceProxy(const std::string& id, Audio::sBuffer buffer)
	: Proxy(id), loadPath(""), isStreamed(false), source(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
	properties.buffer = buffer;
	changedProperties.buffer = true;
}
SourceProxy::SourceProxy(const std::string& id, BufferReference buffer)
	: Proxy(id), loadPath(""), isStreamed(false), source(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
	ReadReference<BufferProxy> buff(buffer);
	setBuffer(buff->getBuffer());
}
const Audio::sSource SourceProxy::getSource() const
{
	return source;
}

/* Setters */
void SourceProxy::setPitch(float pitch)
{
	properties.pitch = pitch;
	changedProperties.pitch = true;
}
void SourceProxy::setGain(float gain)
{
	properties.gain = gain;
	changedProperties.gain = true;
}
void SourceProxy::setPosition(float x, float y, float z)
{
	properties.pos.x = x;
	properties.pos.y = y;
	properties.pos.z = z;
	changedProperties.pos = true;
}
void SourceProxy::setPosition(const glm::vec3& pos)
{
	properties.pos = pos;
	changedProperties.pos = true;
}
void SourceProxy::setRelativity(bool shouldBeRelative)
{
	properties.relativity = shouldBeRelative;
	changedProperties.relativity = true;
}
void SourceProxy::setMinimumDistance(float minDist)
{
	properties.minDist = minDist;
	changedProperties.minDist = true;
}
void SourceProxy::setAttenuation(float attenuation)
{
	properties.attenuation = attenuation;
	changedProperties.attenuation = true;
}
void SourceProxy::setLooping(bool looping)
{
	properties.looping = looping;
	changedProperties.looping = true;
}
void SourceProxy::setFilter(Audio::sFilter nfilter)
{
	properties.filter = nfilter;
	changedProperties.filter = true;
}
void SourceProxy::setAuxiliaryEffectSlot(Audio::sAuxiliaryEffectSlot aux)
{
	properties.aux = aux;
	changedProperties.aux = true;
}
void SourceProxy::setLoadPath(const std::string& loadpath)
{
	if(isStreamed) loadPath = loadpath;
}
void SourceProxy::setBuffer(Audio::sBuffer buff)
{
	if(!isStreamed) { properties.buffer = buff;
		changedProperties.buffer = true;
	}
}

/* Getters */
float SourceProxy::getPitch(void) const
{
	return properties.pitch;
}
float SourceProxy::getGain(void) const
{
	return properties.gain;
}
const glm::vec3& SourceProxy::getPosition(void) const
{
	return properties.pos;
}
bool SourceProxy::getRelativity(void) const
{
	return properties.relativity;
}
float SourceProxy::getMinimumDistance(void) const
{
	return properties.minDist;
}
float SourceProxy::getAttenuation(void) const
{
	return properties.attenuation;
}
ALint SourceProxy::getStatus(void) const
{
	if(source) return source->getStatus();
	else return AL_STOPPED;
}
bool SourceProxy::getLooping(void) const
{
	return properties.looping;
}
const Audio::sFilter SourceProxy::getFilter() const
{
	return properties.filter;
}
const Audio::sAuxiliaryEffectSlot SourceProxy::getAuxiliaryEffectSlot() const
{
	return properties.aux;
}
const std::string& SourceProxy::getLoadPath() const
{
	return loadPath;
}
const Audio::sBuffer SourceProxy::getBuffer() const
{
	return properties.buffer;
}

/* Actually used functions */
void SourceProxy::setAuxiliaryEffectSlot(AuxiliaryEffectReference aux)
{
	ReadReference<AuxiliaryEffectProxy> auxiliary(aux);
	setAuxiliaryEffectSlot(auxiliary->getAuxiliaryEffectSlot());
}
void SourceProxy::setFilter(LowpassFilterReference flt)
{
	ReadReference<LowpassFilterProxy> filter(flt);
	setFilter(filter->getFilter());
}
void SourceProxy::setFilter(HighpassFilterReference flt)
{
	ReadReference<HighpassFilterProxy> filter(flt);
	setFilter(filter->getFilter());
}
void SourceProxy::setFilter(BandpassFilterReference flt)
{
	ReadReference<BandpassFilterProxy> filter(flt);
	setFilter(filter->getFilter());
}
void SourceProxy::setBuffer(BufferReference buff)
{
	ReadReference<BufferProxy> buffer(buff);
	setBuffer(buffer->getBuffer());
}

void SourceProxy::play() const
{
	if(source) source->play();
}
void SourceProxy::pause() const
{
	if(source) source->pause();
}
void SourceProxy::stop() const
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
SourceReference SourceManager::commit(const SourceProxy& proxy)
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
	Abstract::sFIO readah;
	if(proxy.isStreamed) readah = PhysFS::FileHandle::openRead(proxy.loadPath);
	pushCommand( [proxy, ref, readah ](pGameSystem sys) {
	(void)(sys);
	Storage<SourceProxy> &prxy = *ref;
	prxy.beginSet();
	if(proxy.isStreamed) prxy->source = sys->getSoundsys()->createStreamingAudio(readah,4);
	else prxy->source = sys->getSoundsys()->createSoundSource();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
