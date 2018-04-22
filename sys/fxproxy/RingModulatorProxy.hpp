#ifndef RINGMODULATORPROXY_HPP
#define RINGMODULATORPROXY_HPP
#include "../../audio/FX/RingModulatorEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(RingModulatorProxy)
DEFINE_CLASS(RingModulatorManager)
typedef Reference<RingModulatorProxy> RingModulatorReference;

class RingModulatorProxy : public Proxy
{
public:
	friend class RingModulatorManager;
	typedef Audio::WaveformEffect::Waveform Waveform;
private:
	struct {
		bool waveform : 1;
		bool frequency : 1;
		bool highpassCutoff : 1;
	} changedProperties;
	struct {
		Waveform waveform;
		float frequency;
		float highpassCutoff;
	} properties;
	Audio::sRingModulatorEffect effect;
	void queryData();
	void commitData();
public:
	RingModulatorProxy();
	RingModulatorProxy(const RingModulatorProxy& cpy);
	RingModulatorProxy(const std::string& id);
	const Audio::sRingModulatorEffect getEffect() const;

	void setWaveform(Waveform waveform);
	Waveform getWaveform(void) const;

	void setFrequency(float frequency);
	float getFrequency(void) const;
	void setHighpassCutoff(float highpassCutoff);
	float getHighpassCutoff(void) const;
};


class RingModulatorManager : public ResourceManager
{
	friend class RingModulatorProxy;
	typedef MapTrait<RingModulatorProxy,std::string> RingModulatorMap;
	typedef RingModulatorMap::HashIterator VocalMorpherIterator;
private:
	RingModulatorMap buffmp;
public:
	RingModulatorManager() = default;
	~RingModulatorManager() = default;
	RingModulatorReference query(const RingModulatorProxy& proxy);
	RingModulatorReference query(const std::string& key);
	RingModulatorReference commit(const RingModulatorProxy& proxy);
};

#endif // RINGMODULATORPROXY_HPP
