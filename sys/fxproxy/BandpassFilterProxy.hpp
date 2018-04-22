#ifndef BANDPASSFILTERPROXY_HPP
#define BANDPASSFILTERPROXY_HPP
#include "../../audio/FX/BandpassFilter.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(BandpassFilterProxy)
DEFINE_CLASS(BandpassFilterManager)
typedef Reference<BandpassFilterProxy> BandpassFilterReference;

class BandpassFilterProxy : public Proxy
{
public:
	friend class BandpassFilterManager;
private:
	struct {
		bool gain : 1;
		bool highFrequencyGain : 1;
		bool lowFrequencyGain : 1;
	} changedProperties;
	struct {
		float gain;
		float highFrequencyGain;
		float lowFrequencyGain;
	} properties;
	Audio::sBandpassFilter filter;
	void queryData();
	void commitData();
public:
	BandpassFilterProxy();
	BandpassFilterProxy(const BandpassFilterProxy& cpy);
	BandpassFilterProxy(const std::string& id);
	const Audio::sBandpassFilter getFilter() const;

	void setGain(float gain);
	float getGain() const;
	void setHighFrequencyGain(float gain);
	float getHighFrequencyGain() const;
	void setLowFrequencyGain(float gain);
	float getLowFrequencyGain() const;
};

class BandpassFilterManager : public ResourceManager
{
public:
	friend class BandpassFilterProxy;
	typedef MapTrait<BandpassFilterProxy,std::string> BandpassFilterMap;
	typedef BandpassFilterMap::HashIterator BandpassFilterIterator;
private:
	BandpassFilterMap buffmp;
public:
	BandpassFilterManager() = default;
	~BandpassFilterManager() = default;
	BandpassFilterReference query(const BandpassFilterProxy& proxy);
	BandpassFilterReference query(const std::string& key);
	BandpassFilterReference commit(const BandpassFilterProxy& proxy);
};

#endif // BANDPASSFILTERPROXY_HPP
