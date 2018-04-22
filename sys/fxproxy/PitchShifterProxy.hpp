#ifndef PITCHSHIFTERPROXY_HPP
#define PITCHSHIFTERPROXY_HPP
#include "../../audio/FX/PitchShifterEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(PitchShifterProxy)
DEFINE_CLASS(PitchShifterManager)
typedef Reference<PitchShifterProxy> PitchShifterReference;

class PitchShifterProxy : public Proxy
{
public:
	friend class PitchShifterManager;
private:
	struct {
		bool coarseTune : 1;
		bool fineTune : 1;
	} changedProperties;
	struct {
		int coarseTune;
		int fineTune;
	} properties;
	Audio::sPitchShifterEffect effect;
	void queryData();
	void commitData();
public:
	PitchShifterProxy();
	PitchShifterProxy(const PitchShifterProxy& cpy);
	PitchShifterProxy(const std::string& id);
	const Audio::sPitchShifterEffect getEffect() const;

	void setCoarseTune(int courseTune);
	int getCoarseTune(void) const;
	void setFineTune(int fineTune);
	int getFineTune(void) const;
};

class PitchShifterManager : public ResourceManager
{
public:
	friend class PitchShifterProxy;
	typedef MapTrait<PitchShifterProxy,std::string> PitchShifterMap;
	typedef PitchShifterMap::HashIterator PitchShifterIterator;
private:
	PitchShifterMap buffmp;
public:
	PitchShifterManager() = default;
	~PitchShifterManager() = default;
	PitchShifterReference query(const PitchShifterProxy& proxy);
	PitchShifterReference query(const std::string& key);
	PitchShifterReference commit(const PitchShifterProxy& proxy);
};

#endif // PITCHSHIFTERPROXY_HPP
