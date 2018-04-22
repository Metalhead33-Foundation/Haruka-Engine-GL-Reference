#ifndef REVERBPROXY_HPP
#define REVERBPROXY_HPP
#include "../../audio/FX/ReverbEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(ReverbProxy)
DEFINE_CLASS(ReverbManager)
typedef Reference<ReverbProxy> ReverbReference;

class ReverbProxy : public Proxy
{
public:
	friend class ReverbManager;
private:
	struct
	{
		bool density : 1;
		bool diffusion : 1;
		bool gain : 1;
		bool highFrequencyGain : 1;
		bool decayTime : 1;
		bool highFrequencyRatio : 1;
		bool reflectionsGain : 1;
		bool reflectionsDelay : 1;
		bool lateReverbGain : 1;
		bool lateReverbDelay : 1;
		bool roomRolloffFactor : 1;
		bool highFrequencyAirAbsorbtionGain : 1;
		bool highFrequencyDecayLimit : 1;
	} changedProperties;
	struct
	{
		float density;
		float diffusion;
		float gain;
		float highFrequencyGain;
		STime decayTime;
		float highFrequencyRatio;
		float reflectionsGain;
		STime reflectionsDelay;
		float lateReverbGain;
		STime lateReverbDelay;
		float roomRolloffFactor;
		float highFrequencyAirAbsorbtionGain;
		bool highFrequencyDecayLimit;
	} properties;
	Audio::sReverbEffect effect;
	void queryData();
	void commitData();
public:
	ReverbProxy();
	ReverbProxy(const ReverbProxy& cpy);
	ReverbProxy(const std::string& id);
	const Audio::sReverbEffect getEffect() const;
	void setDensity(float density);
	float getDensity(void) const;
	void setDiffusion(float diffusion);
	float getDiffusion(void) const;
	void setGain(float gain);
	float getGain(void) const;
	void setHighFrequencyGain(float gain);
	float getHighFrequencyGain(void) const;
	void setDecayTime(const STime& time);
	const STime& getDecayTime(void) const;
	void setDecayHighFrequencyRatio(float hfratio);
	float getDecayHighFrequencyRatio(void) const;
	void setReflectionsGain(float gain);
	float getReflectionsGain(void) const;
	void setReflectionsDelay(const STime& time);
	const STime& getReflectionsDelay(void) const;
	void setLateReverbGain(float gain);
	float getLateReverbGain(void) const;
	void setLateReverbDelay(const STime& time);
	const STime& getLateReverbDelay(void) const;
	void setRoomRolloffFactor(float factor);
	float getRoomRolloffFactor(void) const;
	void setHighFrequencyAirAbsorbtionGain(float gain);
	float getHighFrequencyAirAbsorbtionGain(void) const;
	void setHighFrequencyDecayLimit(bool limit);
	bool getHighFrequencyDecayLimit(void) const;
};

class ReverbManager : public ResourceManager
{
public:
	friend class ReverbProxy;
	typedef MapTrait<ReverbProxy,std::string> ReverbMap;
	typedef ReverbMap::HashIterator ReverbIterator;
private:
	ReverbMap buffmp;
public:
	ReverbManager() = default;
	~ReverbManager() = default;
	ReverbReference query(const ReverbProxy& proxy);
	ReverbReference query(const std::string& key);
	ReverbReference commit(const ReverbProxy& proxy);
};

#endif // REVERBPROXY_HPP
