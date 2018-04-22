#ifndef VOCALMORPHERPROXY_HPP
#define VOCALMORPHERPROXY_HPP
#include "../../audio/FX/VocalMorpherEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(VocalMorpherProxy)
DEFINE_CLASS(VocalMorpherManager)
typedef Reference<VocalMorpherProxy> VocalMorpherReference;

class VocalMorpherProxy : public Proxy
{
public:
	friend class VocalMorpherManager;
	typedef Audio::WaveformEffect::Waveform Waveform;
private:
	struct {
		bool waveform : 1;
		bool phonemeA : 1;
		bool phonemeB : 1;
		bool coarseTuneA : 1;
		bool coarseTuneB : 1;
		bool morpherRate : 1;
	} changedProperties;
	struct {
		Waveform waveform;
		char phonemeA;
		char phonemeB;
		char coarseTuneA;
		char coarseTuneB;
		float morpherRate;
	} properties;
	Audio::sVocalMorpherEffect effect;
	void queryData();
	void commitData();
public:
	VocalMorpherProxy();
	VocalMorpherProxy(const VocalMorpherProxy& cpy);
	VocalMorpherProxy(const std::string& id);
	const Audio::sVocalMorpherEffect getEffect() const;


	void setWaveform(Waveform waveform);
	Waveform getWaveform(void) const;

	void setPhonemeA(char phonemeA);
	void setPhonemeB(char phonemeB);
	void setCoarseTuneA(char coarseTuneA);
	void setCoarseTuneB(char coarseTuneB);
	void setMorpherRate(float morpherRate);

	char getPhonemeA(void) const;
	char getPhonemeB(void) const;
	char getCoarseTuneA(void) const;
	char getCoarseTuneB(void) const;
	float getMorpherRate(void) const;
};


class VocalMorpherManager : public ResourceManager
{
	friend class VocalMorpherProxy;
	typedef MapTrait<VocalMorpherProxy,std::string> VocalMorpherMap;
	typedef VocalMorpherMap::HashIterator VocalMorpherIterator;
private:
	VocalMorpherMap buffmp;
public:
	VocalMorpherManager() = default;
	~VocalMorpherManager() = default;
	VocalMorpherReference query(const VocalMorpherProxy& proxy);
	VocalMorpherReference query(const std::string& key);
	VocalMorpherReference commit(const VocalMorpherProxy& proxy);
};

#endif // VOCALMORPHERPROXY_HPP
