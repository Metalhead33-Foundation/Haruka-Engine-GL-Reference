#ifndef AUXILIARYEFFECTPROXY_HPP
#define AUXILIARYEFFECTPROXY_HPP
#include "../../audio/FX/AuxiliaryEffectSlot.hpp"
#include "../fxproxy/AllEffects.hpp"
#include "../fxproxy/AllFilters.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(AuxiliaryEffectProxy)
DEFINE_CLASS(AuxiliaryEffectManager)
typedef Reference<AuxiliaryEffectProxy> AuxiliaryEffectReference;

class AuxiliaryEffectProxy : public Proxy
{
public:
	friend class AuxiliaryEffectManager;
private:
	struct {
		bool gain : 1;
		bool sendAudio : 1;
		bool effect : 1;
		bool filter : 1;
	} changedProperties;
	struct {
		float gain;
		bool sendAudio;
		Audio::sEffect effect;
		Audio::sFilter filter;
	} properties;
	Audio::sAuxiliaryEffectSlot effectSlot;
	void queryData();
	void commitData();
public:
	AuxiliaryEffectProxy();
	AuxiliaryEffectProxy(const AuxiliaryEffectProxy& cpy);
	AuxiliaryEffectProxy(const std::string& id);
	const Audio::sAuxiliaryEffectSlot getAuxiliaryEffectSlot() const;

	void setGain(float gain);
	float getGain(void) const;
	void setSendAudio(bool setto);
	bool getSendAudio(void) const;
	void setEffect(const Audio::sEffect eff);
	const Audio::sEffect getEffect() const;
	void setFilter(const Audio::sFilter flt);
	const Audio::sFilter getFilter() const;

	void setEffect(ChorflangReference eff);
	void setEffect(CompressorReference eff);
	void setEffect(DistortionReference eff);
	void setEffect(EchoReference eff);
	void setEffect(EqualizerReference eff);
	void setEffect(FrequencyShifterReference eff);
	void setEffect(PitchShifterReference eff);
	void setEffect(ReverbReference eff);
	void setEffect(RingModulatorReference eff);
	void setEffect(VocalMorpherReference eff);
	void setEffect(WahWahReference eff);

	void setFilter(LowpassFilterReference flt);
	void setFilter(HighpassFilterReference flt);
	void setFilter(BandpassFilterReference flt);
};

class AuxiliaryEffectManager : public ResourceManager
{
public:
	friend class AuxiliaryEffectProxy;
	typedef MapTrait<AuxiliaryEffectProxy,std::string> AuxiliaryEffectMap;
	typedef AuxiliaryEffectMap::HashIterator AuxiliaryEffectIterator;
private:
	AuxiliaryEffectMap buffmp;
public:
	AuxiliaryEffectManager() = default;
	~AuxiliaryEffectManager() = default;
	AuxiliaryEffectReference query(const AuxiliaryEffectProxy& proxy);
	AuxiliaryEffectReference query(const std::string& key);
	AuxiliaryEffectReference commit(const AuxiliaryEffectProxy& proxy);
};
#endif // AUXILIARYEFFECTPROXY_HPP
