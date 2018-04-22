#ifndef ECHOPROXY_HPP
#define ECHOPROXY_HPP
#include "../../audio/FX/EchoEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(EchoProxy)
DEFINE_CLASS(EchoManager)
typedef Reference<EchoProxy> EchoReference;

class EchoProxy : public Proxy
{
public:
	friend class EchoManager;
private:
	struct {
		bool delay : 1;
		bool lDelay : 1;
		bool damping : 1;
		bool feedback : 1;
		bool spread : 1;
	} changedProperties;
	struct {
		STime delay;
		STime lDelay;
		float damping;
		float feedback;
		float spread;
	} properties;
	Audio::sEchoEffect effect;
	void queryData();
	void commitData();
public:
	EchoProxy();
	EchoProxy(const EchoProxy& cpy);
	EchoProxy(const std::string& id);
	const Audio::sEchoEffect getEffect() const;

	void setDelay(const STime& rate);
	const STime& getDelay(void) const;
	void setLRDelay(const STime& rate);
	const STime& getLRDelay(void) const;
	void setDamping(float damping);
	float getDamping(void) const;
	void setFeedback(float feedback);
	float getFeedback(void) const;
	void setSpread(float spread);
	float getSpread(void) const;
};

class EchoManager : public ResourceManager
{
public:
	friend class EchoProxy;
	typedef MapTrait<EchoProxy,std::string> EchoMap;
	typedef EchoMap::HashIterator EchoIterator;
private:
	EchoMap buffmp;
public:
	EchoManager() = default;
	~EchoManager() = default;
	EchoReference query(const EchoProxy& proxy);
	EchoReference query(const std::string& key);
	EchoReference commit(const EchoProxy& proxy);
};
#endif // ECHOPROXY_HPP
