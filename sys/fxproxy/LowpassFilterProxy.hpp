#ifndef LOWPASSFILTERPROXY_HPP
#define LOWPASSFILTERPROXY_HPP
#include "../../audio/FX/LowpassFilter.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(LowpassFilterProxy)
DEFINE_CLASS(LowpassFilterManager)
typedef Reference<LowpassFilterProxy> LowpassFilterReference;

class LowpassFilterProxy : public Proxy
{
public:
	friend class LowpassFilterManager;
private:
	struct {
		bool gain : 1;
		bool highFrequencyGain : 1;
	} changedProperties;
	struct {
		float gain;
		float highFrequencyGain;
	} properties;
	Audio::sLowpassFilter filter;
	void queryData();
	void commitData();
public:
	LowpassFilterProxy();
	LowpassFilterProxy(const LowpassFilterProxy& cpy);
	LowpassFilterProxy(const std::string& id);
	const Audio::sLowpassFilter getFilter() const;

	void setGain(float gain);
	float getGain() const;
	void setHighFrequencyGain(float gain);
	float getHighFrequencyGain() const;
};

class LowpassFilterManager : public ResourceManager
{
public:
	friend class LowpassFilterProxy;
	typedef MapTrait<LowpassFilterProxy,std::string> LowpassFilterMap;
	typedef LowpassFilterMap::HashIterator LowpassFilterIterator;
private:
	LowpassFilterMap buffmp;
public:
	LowpassFilterManager() = default;
	~LowpassFilterManager() = default;
	LowpassFilterReference query(const LowpassFilterProxy& proxy);
	LowpassFilterReference query(const std::string& key);
	LowpassFilterReference commit(const LowpassFilterProxy& proxy);
};
#endif // LOWPASSFILTERPROXY_HPP
