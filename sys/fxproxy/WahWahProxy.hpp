#ifndef WAHWAHPROXY_HPP
#define WAHWAHPROXY_HPP
#include "../../audio/FX/WahWahEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(WahWahProxy)
DEFINE_CLASS(WahWahManager)
typedef Reference<WahWahProxy> WahWahReference;

class WahWahProxy : public Proxy
{
public:
	friend class WahWahManager;
private:
	struct {
		bool attackTime : 1;
		bool releaseTime : 1;
		bool resonance : 1;
		bool peakGain : 1;
	} changedProperties;
	struct {
		STime attackTime;
		STime releaseTime;
		float resonance;
		float peakGain;
	} properties;
	Audio::sWahWahEffect effect;
	void queryData();
	void commitData();
public:
	WahWahProxy();
	WahWahProxy(const WahWahProxy& cpy);
	WahWahProxy(const std::string& id);
	const Audio::sWahWahEffect getEffect() const;

	void setAttackTime(const STime& time);
	const STime& getAttackTime(void) const;
	void setReleaseTime(const STime& time);
	const STime& getReleaseTime(void) const;
	void setResonance(float resonance);
	float getResonance(void) const;
	void setPeakGain(float peakGain);
	float getPeakGain(void) const;
};

class WahWahManager : public ResourceManager
{
	friend class WahWahProxy;
	typedef MapTrait<WahWahProxy,std::string> WahWahMap;
	typedef WahWahMap::HashIterator WahWahIterator;
private:
	WahWahMap buffmp;
public:
	WahWahManager() = default;
	~WahWahManager() = default;
	WahWahReference query(const WahWahProxy& proxy);
	WahWahReference query(const std::string& key);
	WahWahReference commit(const WahWahProxy& proxy);
};

#endif // WAHWAHPROXY_HPP
