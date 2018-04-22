#include "ChorflangProxy.hpp"
#include "../../audio/FX/ChorusEffect.hpp"
#include "../../audio/FX/FlangerEffect.hpp"
#include <cstring>

void ChorflangProxy::queryData()
{
	if(effect)
	{
		properties.delay = effect->getDelay();
		changedProperties.delay = false;
		properties.depth = effect->getDepth();
		changedProperties.depth = false;
		properties.feedback = effect->getFeedback();
		changedProperties.feedback = false;
		properties.isWaveformTriangle = effect->getIsWaveformTriangle();
		changedProperties.isWaveformTriangle = false;
		properties.phase = effect->getPhase();
		changedProperties.phase = false;
		properties.rate = effect->getRate();
		changedProperties.rate = false;
	}
}
void ChorflangProxy::commitData()
{
	if(effect)
	{
		if(changedProperties.delay)
		{
			effect->setDelay(properties.delay);
			changedProperties.delay = false;
		}
		if(changedProperties.depth)
		{
			effect->setDepth(properties.depth);
			changedProperties.depth = false;
		}
		if(changedProperties.feedback)
		{
			effect->setFeedback(properties.feedback);
			changedProperties.feedback = false;
		}
		if(changedProperties.isWaveformTriangle)
		{
			effect->setIsWaveformTriangle(properties.isWaveformTriangle);
			changedProperties.isWaveformTriangle = false;
		}
		if(changedProperties.phase)
		{
			effect->setPhase(properties.phase);
			changedProperties.phase = false;
		}
		if(changedProperties.rate)
		{
			effect->setRate(properties.rate);
			changedProperties.rate = false;
		}
	}
}
ChorflangProxy::ChorflangProxy()
	: Proxy(""), isFlanger(false), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
}
ChorflangProxy::ChorflangProxy(const ChorflangProxy& cpy)
	: Proxy(cpy.Id), isFlanger(cpy.isFlanger), effect(cpy.effect)
{
	this->properties = cpy.properties;
	this->changedProperties = cpy.changedProperties;
}
ChorflangProxy::ChorflangProxy(const std::string& id, bool flanger)
	: Proxy(id), isFlanger(flanger), effect(nullptr)
{
	memset(&changedProperties, 0, sizeof(changedProperties));
	memset(&properties, 0, sizeof(properties));
} // We assume Chorus by default

void ChorflangProxy::setIsWaveformTriangle(bool isWaveformTriangle)
{
	properties.isWaveformTriangle = isWaveformTriangle;
	changedProperties.isWaveformTriangle = true;
}
bool ChorflangProxy::getIsWaveformTriangle(void) const
{
	return properties.isWaveformTriangle;
}
void ChorflangProxy::setPhase(int phase)
{
	properties.phase = phase;
	changedProperties.phase = true;
}
int ChorflangProxy::getPhase(void) const
{
	return properties.phase;
}
void ChorflangProxy::setRate(float rate)
{
	properties.rate = rate;
	changedProperties.rate = true;
}
float ChorflangProxy::getRate(void) const
{
	return properties.rate;
}
void ChorflangProxy::setDepth(float rate)
{
	properties.depth = rate;
	changedProperties.depth = true;
}
float ChorflangProxy::getDepth(void) const
{
	return properties.depth;
}
void ChorflangProxy::setFeedback(float rate)
{
	properties.feedback = rate;
	changedProperties.feedback = true;
}
float ChorflangProxy::getFeedback(void) const
{
	return properties.feedback;
}
void ChorflangProxy::setDelay(const STime& rate)
{
	properties.delay = rate;
	changedProperties.delay = true;
}
const STime& ChorflangProxy::getDelay(void) const
{
	return properties.delay;
}
const Audio::sChorflangEffect ChorflangProxy::getEffect() const
{
	return effect;
}

ChorflangReference ChorflangManager::query(const ChorflangProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	ChorflangReference ref;
	if(it == buffmp.end())
	{
		ref = ChorflangReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
ChorflangReference ChorflangManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	ChorflangReference ref;
	if(it == buffmp.end())
	{
		ref = ChorflangReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
ChorflangReference ChorflangManager::commit(const ChorflangProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	if(ref->isInitialized())
	{
		ref->invalidate();
		pushCommand( [proxy, ref ](pGameSystem sys) {
			(void)(sys);
			Storage<ChorflangProxy> &prxy = *ref;
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
	Storage<ChorflangProxy> &prxy = *ref;
	prxy.beginSet();
	if(proxy.isFlanger)	prxy->effect = Audio::FlangerEffect::create();
	else prxy->effect = Audio::ChorusEffect::create();
	prxy->changedProperties = proxy.changedProperties;
	prxy->properties = proxy.properties;
	prxy->commitData();
	prxy->queryData();
	prxy.endSet();
	});
	return ref;
}
