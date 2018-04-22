#ifndef HIGHPASSFILTERPROXY_HPP
#define HIGHPASSFILTERPROXY_HPP
#include "../../audio/FX/HighpassFilter.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(HighpassFilterProxy)
DEFINE_CLASS(HighpassFilterManager)
typedef Reference<HighpassFilterProxy> HighpassFilterReference;

class HighpassFilterProxy : public Proxy
{
public:
	friend class HighpassFilterManager;
private:
	struct {
		bool gain : 1;
		bool lowFrequencyGain : 1;
	} changedProperties;
	struct {
		float gain;
		float lowFrequencyGain;
	} properties;
	Audio::sHighpassFilter filter;
	void queryData();
	void commitData();
public:
	HighpassFilterProxy();
	HighpassFilterProxy(const HighpassFilterProxy& cpy);
	HighpassFilterProxy(const std::string& id);
	const Audio::sHighpassFilter getFilter() const;

	void setGain(float gain);
	float getGain() const;
	void setLowFrequencyGain(float gain);
	float getLowFrequencyGain() const;
};

class HighpassFilterManager : public ResourceManager
{
public:
	friend class HighpassFilterProxy;
	typedef MapTrait<HighpassFilterProxy,std::string> HighpassFilterMap;
	typedef HighpassFilterMap::HashIterator HighpassFilterIterator;
private:
	HighpassFilterMap buffmp;
public:
	HighpassFilterManager() = default;
	~HighpassFilterManager() = default;
	HighpassFilterReference query(const HighpassFilterProxy& proxy);
	HighpassFilterReference query(const std::string& key);
	HighpassFilterReference commit(const HighpassFilterProxy& proxy);
};
#endif // HIGHPASSFILTERPROXY_HPP
