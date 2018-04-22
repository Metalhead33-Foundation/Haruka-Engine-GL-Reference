#ifndef COMPRESSORPROXY_HPP
#define COMPRESSORPROXY_HPP
#include "../../audio/FX/CompressorEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(CompressorProxy)
DEFINE_CLASS(CompressorManager)
typedef Reference<CompressorProxy> CompressorReference;

class CompressorProxy : public Proxy
{
public:
	friend class CompressorManager;
private:
	struct {
		bool isOn : 1;
	} changedProperties;
	struct {
		bool isOn;
	} properties;
	Audio::sCompressorEffect effect;
	void queryData();
	void commitData();
public:
	CompressorProxy();
	CompressorProxy(const CompressorProxy& cpy);
	CompressorProxy(const std::string& id);
	const Audio::sCompressorEffect getEffect() const;

	void turnOn();
	void turnOff();
	bool isOn() const;
};

class CompressorManager : public ResourceManager
{
public:
	friend class CompressorProxy;
	typedef MapTrait<CompressorProxy,std::string> CompressorMap;
	typedef CompressorMap::HashIterator CompressorIterator;
private:
	CompressorMap buffmp;
public:
	CompressorManager() = default;
	~CompressorManager() = default;
	CompressorReference query(const CompressorProxy& proxy);
	CompressorReference query(const std::string& key);
	CompressorReference commit(const CompressorProxy& proxy);
};

#endif // COMPRESSORPROXY_HPP
