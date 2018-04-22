#ifndef EQUALIZERPROXY_HPP
#define EQUALIZERPROXY_HPP
#include "../../audio/FX/EqualizerEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(EqualizerProxy)
DEFINE_CLASS(EqualizerManager)
typedef Reference<EqualizerProxy> EqualizerReference;

class EqualizerProxy : public Proxy
{
public:
	friend class EqualizerManager;
private:
	struct {
		bool lowGain : 1;
		bool lowCutoff : 1;
		bool mid1Gain : 1;
		bool mid1Center : 1;
		bool mid1Width : 1;
		bool mid2Gain : 1;
		bool mid2Center : 1;
		bool mid2Width : 1;
		bool highGain : 1;
		bool highCutoff : 1;
	} changedProperties;
	struct {
		float lowGain;
		float lowCutoff;
		float mid1Gain;
		float mid1Center;
		float mid1Width;
		float mid2Gain;
		float mid2Center;
		float mid2Width;
		float highGain;
		float highCutoff;
	} properties;
	Audio::sEqualizerEffect effect;
	void queryData();
	void commitData();
public:
	EqualizerProxy();
	EqualizerProxy(const EqualizerProxy& cpy);
	EqualizerProxy(const std::string& id);
	const Audio::sEqualizerEffect getEffect() const;

	void setLowGain(float lowGain);
	void setLowCutoff(float lowCutoff);
	void setMid1Gain(float mid1Gain);
	void setMid1Center(float mid1Center);
	void setMid1Width(float mid1Width);
	void setMid2Gain(float mid1Gain);
	void setMid2Center(float mid1Center);
	void setMid2Width(float mid1Width);
	void setHighGain(float highGain);
	void setHighCutoff(float highCutoff);

	float getLowGain(void) const;
	float getLowCutoff(void) const;
	float getMid1Gain(void) const;
	float getMid1Center(void) const;
	float getMid1Width(void) const;
	float getMid2Gain(void) const;
	float getMid2Center(void) const;
	float getMid2Width(void) const;
	float getHighGain(void) const;
	float getHighCutoff(void) const;

};

class EqualizerManager : public ResourceManager
{
public:
	friend class EqualizerProxy;
	typedef MapTrait<EqualizerProxy,std::string> EqualizerMap;
	typedef EqualizerMap::HashIterator EqualizerIterator;
private:
	EqualizerMap buffmp;
public:
	EqualizerManager() = default;
	~EqualizerManager() = default;
	EqualizerReference query(const EqualizerProxy& proxy);
	EqualizerReference query(const std::string& key);
	EqualizerReference commit(const EqualizerProxy& proxy);
};

#endif // EQUALIZERPROXY_HPP
