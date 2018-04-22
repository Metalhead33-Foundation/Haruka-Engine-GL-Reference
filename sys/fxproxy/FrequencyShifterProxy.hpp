#ifndef FREQUENCYSHIFTERPROXY_HPP
#define FREQUENCYSHIFTERPROXY_HPP
#include "../../audio/FX/FrequencyShifterEffect.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../ResourceManager.hpp"

DEFINE_CLASS(FrequencyShifterProxy)
DEFINE_CLASS(FrequencyShifterManager)
typedef Reference<FrequencyShifterProxy> FrequencyShifterReference;

class FrequencyShifterProxy : public Proxy
{
public:
	friend class FrequencyShifterManager;
private:
	struct {
		bool frequency : 1;
		bool leftDirection : 1;
		bool rightDirection : 1;
	} changedProperties;
	struct {
		float frequency;
		int leftDirection;
		int rightDirection;
	} properties;
	Audio::sFrequencyShifterEffect effect;
	void queryData();
	void commitData();
public:
	FrequencyShifterProxy();
	FrequencyShifterProxy(const FrequencyShifterProxy& cpy);
	FrequencyShifterProxy(const std::string& id);
	const Audio::sFrequencyShifterEffect getEffect() const;

	void setFrequency(float frequency);
	float getFrequency(void) const;
	void setLeftDirection(int leftDirection);
	int getLeftDirection(void) const;
	void setRightDirection(int rightDirection);
	int getRightDirection(void) const;
};

class FrequencyShifterManager : public ResourceManager
{
public:
	friend class FrequencyShifterProxy;
	typedef MapTrait<FrequencyShifterProxy,std::string> FrequencyShifterMap;
	typedef FrequencyShifterMap::HashIterator PitchShifterIterator;
private:
	FrequencyShifterMap buffmp;
public:
	FrequencyShifterManager() = default;
	~FrequencyShifterManager() = default;
	FrequencyShifterReference query(const FrequencyShifterProxy& proxy);
	FrequencyShifterReference query(const std::string& key);
	FrequencyShifterReference commit(const FrequencyShifterProxy& proxy);
};

#endif // FREQUENCYSHIFTERPROXY_HPP
