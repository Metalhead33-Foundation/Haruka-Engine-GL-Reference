#include "ReverbProxy.hpp"
#include <cstring>

ReverbProxy::ReverbProxy()
	: Proxy(""), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
ReverbProxy::ReverbProxy(const ReverbProxy& cpy)
	: Proxy(cpy.Id), effect(cpy.effect)
{
	properties = cpy.properties;
	changedProperties = cpy.changedProperties;
}
ReverbProxy::ReverbProxy(const std::string& id)
	: Proxy(id), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
const Audio::sReverbEffect ReverbProxy::getEffect() const
{
	return effect;
}
void ReverbProxy::queryData()
{
	if(effect)
	{
		properties.decayTime = effect->getDecayTime();
		changedProperties.decayTime = false;
		properties.density = effect->getDensity();
		changedProperties.density = false;
		properties.diffusion = effect->getDiffusion();
		changedProperties.diffusion = false;
		properties.gain = effect->getGain();
		changedProperties.gain = false;
		properties.highFrequencyAirAbsorbtionGain = effect->getHighFrequencyAirAbsorbtionGain();
		changedProperties.highFrequencyAirAbsorbtionGain = false;
		properties.highFrequencyDecayLimit = effect->getHighFrequencyDecayLimit();
		changedProperties.highFrequencyDecayLimit = false;
		properties.highFrequencyGain = effect->getHighFrequencyDecayLimit();
		changedProperties.highFrequencyGain = false;
		properties.highFrequencyRatio = effect->getDecayHighFrequencyRatio();
		changedProperties.highFrequencyRatio = false;
		properties.lateReverbDelay = effect->getLateReverbDelay();
		changedProperties.lateReverbDelay = false;
		properties.lateReverbGain = effect->getLateReverbGain();
		changedProperties.lateReverbGain = false;
		properties.reflectionsDelay = effect->getReflectionsDelay();
		changedProperties.reflectionsDelay = false;
		properties.reflectionsGain = effect->getReflectionsGain();
		changedProperties.reflectionsGain = false;
		properties.roomRolloffFactor = effect->getRoomRolloffFactor();
		changedProperties.roomRolloffFactor = false;
	}
}
void ReverbProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.decayTime) {
			effect->setDecayTime(properties.decayTime);
			changedProperties.decayTime = false;
		}
		if(changedProperties.density) {
			effect->setDensity(properties.density);
			changedProperties.density = false;
		}
		if(changedProperties.diffusion) {
			effect->setDiffusion(properties.diffusion);
			changedProperties.diffusion = false;
		}
		if(changedProperties.gain) {
			effect->setGain(properties.gain);
			changedProperties.gain = false;
		}
		if(changedProperties.highFrequencyAirAbsorbtionGain) {
			effect->setHighFrequencyAirAbsorbtionGain(properties.highFrequencyAirAbsorbtionGain);
			changedProperties.highFrequencyAirAbsorbtionGain = false;
		}
		if(changedProperties.highFrequencyDecayLimit) {
			effect->setHighFrequencyDecayLimit(properties.highFrequencyDecayLimit);
			changedProperties.highFrequencyDecayLimit = false;
		}
		if(changedProperties.highFrequencyRatio) {
			effect->setDecayHighFrequencyRatio(properties.highFrequencyRatio);
			changedProperties.highFrequencyRatio = false;
		}
		if(changedProperties.lateReverbDelay) {
			effect->setLateReverbDelay(properties.lateReverbDelay);
			changedProperties.lateReverbDelay = false;
		}
		if(changedProperties.lateReverbGain) {
			effect->setLateReverbGain(properties.lateReverbGain);
			changedProperties.lateReverbGain = false;
		}
		if(changedProperties.reflectionsGain) {
			effect->setReflectionsGain(properties.reflectionsGain);
			changedProperties.reflectionsGain = false;
		}
		if(changedProperties.roomRolloffFactor) {
			effect->setRoomRolloffFactor(properties.roomRolloffFactor);
			changedProperties.roomRolloffFactor = false;
		}
	}
}

void ReverbProxy::setDensity(float density)
{
	properties.density = density;
	changedProperties.density = true;
}
float ReverbProxy::getDensity(void) const
{
	return properties.density;
}
void ReverbProxy::setDiffusion(float diffusion)
{
	properties.diffusion = diffusion;
	changedProperties.diffusion = true;
}
float ReverbProxy::getDiffusion(void) const
{
	return properties.diffusion;
}
void ReverbProxy::setGain(float gain)
{
	properties.gain = gain;
	changedProperties.gain = true;
}
float ReverbProxy::getGain(void) const
{
	return properties.gain;
}
void ReverbProxy::setHighFrequencyGain(float gain)
{
	properties.highFrequencyGain = gain;
	changedProperties.highFrequencyGain = true;
}
float ReverbProxy::getHighFrequencyGain(void) const
{
	return properties.highFrequencyGain;
}
void ReverbProxy::setDecayTime(const STime& time)
{
	properties.decayTime = time;
	changedProperties.decayTime = true;
}
const STime &ReverbProxy::getDecayTime(void) const
{
	return properties.decayTime;
}
void ReverbProxy::setDecayHighFrequencyRatio(float hfratio)
{
	properties.highFrequencyRatio = hfratio;
	changedProperties.highFrequencyRatio = true;
}
float ReverbProxy::getDecayHighFrequencyRatio(void) const
{
	return properties.highFrequencyRatio;
}
void ReverbProxy::setReflectionsGain(float gain)
{
	properties.reflectionsGain = gain;
	changedProperties.reflectionsGain = true;
}
float ReverbProxy::getReflectionsGain(void) const
{
	return properties.reflectionsGain;
}
void ReverbProxy::setReflectionsDelay(const STime& time)
{
	properties.reflectionsDelay = time;
	changedProperties.reflectionsDelay = true;
}
const STime &ReverbProxy::getReflectionsDelay(void) const
{
	return properties.reflectionsDelay;
}
void ReverbProxy::setLateReverbGain(float gain)
{
	properties.lateReverbGain = gain;
	changedProperties.lateReverbGain = true;
}
float ReverbProxy::getLateReverbGain(void) const
{
	return properties.lateReverbGain;
}
void ReverbProxy::setLateReverbDelay(const STime& time)
{
	properties.lateReverbDelay = time;
	changedProperties.lateReverbDelay = true;
}
const STime &ReverbProxy::getLateReverbDelay(void) const
{
	return properties.lateReverbDelay;
}
void ReverbProxy::setRoomRolloffFactor(float factor)
{
	properties.roomRolloffFactor = factor;
	changedProperties.roomRolloffFactor = true;
}
float ReverbProxy::getRoomRolloffFactor(void) const
{
	return properties.roomRolloffFactor;
}
void ReverbProxy::setHighFrequencyAirAbsorbtionGain(float gain)
{
	properties.highFrequencyAirAbsorbtionGain = gain;
	changedProperties.highFrequencyAirAbsorbtionGain = true;
}
float ReverbProxy::getHighFrequencyAirAbsorbtionGain(void) const
{
	return properties.highFrequencyAirAbsorbtionGain;
}
void ReverbProxy::setHighFrequencyDecayLimit(bool limit)
{
	properties.highFrequencyDecayLimit = limit;
	changedProperties.highFrequencyAirAbsorbtionGain = true;
}
bool ReverbProxy::getHighFrequencyDecayLimit(void) const
{
	return properties.highFrequencyDecayLimit;
}

ReverbReference ReverbManager::query(const ReverbProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	ReverbReference ref;
	if(it == buffmp.end())
	{
		ref = ReverbReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
ReverbReference ReverbManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	ReverbReference ref;
	if(it == buffmp.end())
	{
		ref = ReverbReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
ReverbReference ReverbManager::commit(const ReverbProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<ReverbProxy> &prxy = *ref;
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
	Storage<ReverbProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->effect = Audio::ReverbEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
