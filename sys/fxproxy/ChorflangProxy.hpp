#ifndef CHORFLANGPROXY_HPP
#define CHORFLANGPROXY_HPP
#include "../../audio/FX/ChorflangEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(ChorflangProxy)
DEFINE_CLASS(ChorflangManager)
typedef Reference<ChorflangProxy> ChorflangReference;

class ChorflangProxy : public Proxy
{
public:
	friend class ChorflangManager;
private:
	struct {
		bool isWaveformTriangle : 1;
		bool phase : 1;
		bool rate : 1;
		bool depth : 1;
		bool feedback : 1;
		bool delay : 1;
	} changedProperties;
	struct {
		bool isWaveformTriangle;
		int phase;
		float rate;
		float depth;
		float feedback;
		STime delay;
	} properties;
	const bool isFlanger; // We assume Chorus if it's not a flanger
	Audio::sChorflangEffect effect;
	void queryData();
	void commitData();
public:
	ChorflangProxy();
	ChorflangProxy(const ChorflangProxy& cpy);
	ChorflangProxy(const std::string& id, bool flanger = false); // We assume Chorus by default
	const Audio::sChorflangEffect getEffect() const;

	void setIsWaveformTriangle(bool isWaveformTriangle);
	bool getIsWaveformTriangle(void) const;
	void setPhase(int phase);
	int getPhase(void) const;
	void setRate(float rate);
	float getRate(void) const;
	void setDepth(float rate);
	float getDepth(void) const;
	void setFeedback(float rate);
	float getFeedback(void) const;
	void setDelay(const STime& rate);
	const STime& getDelay(void) const;
};

class ChorflangManager : public ResourceManager
{
public:
	friend class ChorflangProxy;
	typedef MapTrait<ChorflangProxy,std::string> ChorflangMap;
	typedef ChorflangMap::HashIterator ChorflangIterator;
private:
	ChorflangMap buffmp;
public:
	ChorflangManager() = default;
	~ChorflangManager() = default;
	ChorflangReference query(const ChorflangProxy& proxy);
	ChorflangReference query(const std::string& key);
	ChorflangReference commit(const ChorflangProxy& proxy);
};

#endif // CHORFLANGPROXY_HPP
