#ifndef DISTORTIONPROXY_HPP
#define DISTORTIONPROXY_HPP
#include "../../audio/FX/DistortionEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(DistortionProxy)
DEFINE_CLASS(DistortionManager)
typedef Reference<DistortionProxy> DistortionReference;

class DistortionProxy : public Proxy
{
public:
	friend class DistortionManager;
private:
	struct {
		bool edge : 1;
		bool gain : 1;
		bool lowPassCutoff : 1;
		bool eQCenter : 1;
		bool eQBandwith : 1;
	} changedProperties;
	struct {
		float edge;
		float gain;
		float lowPassCutoff;
		float eQCenter;
		float eQBandwith;
	} properties;
	Audio::sDistortionEffect effect;
	void queryData();
	void commitData();
public:
	DistortionProxy();
	DistortionProxy(const DistortionProxy& cpy);
	DistortionProxy(const std::string& id);
	const Audio::sDistortionEffect getEffect() const;

	void setEdge(float edge);
	float getEdge(void) const;
	void setGain(float gain);
	float getGain(void) const;
	void setLowPassCutoff(float gain);
	float getLowPassCutoff(void) const;
	void setEQCenter(float gain);
	float getEQCenter(void) const;
	void setEQBandwith(float gain);
	float getEQBandwith(void) const;
};

class DistortionManager : public ResourceManager
{
public:
	friend class DistortionProxy;
	typedef MapTrait<DistortionProxy,std::string> DistortionMap;
	typedef DistortionMap::HashIterator DistortionIterator;
private:
	DistortionMap buffmp;
public:
	DistortionManager() = default;
	~DistortionManager() = default;
	DistortionReference query(const DistortionProxy& proxy);
	DistortionReference query(const std::string& key);
	DistortionReference commit(const DistortionProxy& proxy);
};
#endif // DISTORTIONPROXY_HPP
