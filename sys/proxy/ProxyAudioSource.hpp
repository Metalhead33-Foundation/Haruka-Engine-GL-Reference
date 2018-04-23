#ifndef PROXYAUDIOSOURCE_HPP
#define PROXYAUDIOSOURCE_HPP
#include "AuxiliaryEffectProxy.hpp"
#include "ProxyAudioBuffer.hpp"

DEFINE_CLASS(SourceProxy)
DEFINE_CLASS(SourceManager)
typedef Reference<SourceProxy> SourceReference;

class SourceProxy : public Proxy
{
public:
	friend class SourceManager;
private:
	struct {
		bool pitch : 1;
		bool gain : 1;
		bool pos : 1;
		bool relativity : 1;
		bool minDist : 1;
		bool attenuation : 1;
		bool looping : 1;
		bool filter : 1;
		bool aux : 1;
	} changedProperties;
	struct {
		float pitch;
		bool gain;
		glm::vec3 pos;
		bool relativity;
		float minDist;
		float attenuation;
		bool looping;
		Audio::sFilter filter;
		Audio::sAuxiliaryEffectSlot aux;
	} properties;
	Audio::sAuxiliaryEffectSlot effectSlot;
	Audio::sSource source; // Only relevent if it's not streamed
	std::string loadPath; // Only relevant if audio is streamed
	const bool isStreamed;
	Audio::sBuffer buffer; // Only relevent if it's not streamed

	void queryData();
	void commitData();
public:
	SourceProxy();
	SourceProxy(const SourceProxy& cpy);
	SourceProxy(const std::string& id);
	const Audio::sAudioSource getSource() const;

	/* Setters */
	void setPitch(float pitch);
	void setGain(float gain);
	void setPosition(float x, float y, float z);
	void setPosition(const glm::vec3& pos);
	void setRelativity(bool shouldBeRelative);
	void setMinimumDistance(float minDist);
	void setAttenuation(float attenuation);
	void setLooping(bool looping);
	void setFilter(Audio::sFilter nfilter);
	void setAuxiliaryEffectSlot(Audio::sAuxiliaryEffectSlot aux);
	void setLoadPath(const std::string& loadpath);
	void setBuffer(Audio::sBuffer buff);

	/* Getters */
	float getPitch(void) const;
	float getGain(void) const;
	const glm::vec3& getPosition(void) const;
	bool getRelativity(void) const;
	float getMinimumDistance(void) const;
	float getAttenuation(void) const;
	ALint getStatus(void) const;
	bool getLooping(void) const;
	const sFilter getFilter() const;
	const sAuxiliaryEffectSlot getAuxiliaryEffectSlot() const;
	const std::string& getLoadPath() const;
	const Audio::sBuffer getBuffer() const;

	/* Actually used functions */
	void setAuxiliaryEffectSlot(AuxiliaryEffectReference aux);
	void setFilter(LowpassFilterReference flt);
	void setFilter(HighpassFilterReference flt);
	void setFilter(BandpassFilterReference flt);
	void setBuffer(BufferReference buff);
    
	void play();
	void pause();
	void stop();

};

class SourceManager : public ResourceManager
{
public:
	friend class SourceProxy;
	typedef MapTrait<SourceProxy,std::string> SourceMap;
	typedef SourceMap::HashIterator SourceIterator;
private:
	SourceMap buffmp;
public:
	SourceManager() = default;
	~SourceManager() = default;
	SourceReference query(const SourceProxy& proxy);
	SourceReference query(const std::string& key);
	SourceReference commit(const SourceProxy& proxy);
};
#endif // PROXYAUDIOSOURCE_HPP
