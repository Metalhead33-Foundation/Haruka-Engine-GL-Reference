#ifndef PROXYANIMATEDTEXTURE_HPP
#define PROXYANIMATEDTEXTURE_HPP
#include "../ResourceManager.hpp"
#include "../../abstract/AnimatedTexture.hpp"
#include "../../abstract/HashTrait.hpp"
#include "../STime.hpp"

DEFINE_CLASS(AnimatedTextureProxy)
DEFINE_CLASS(AnimatedTextureManager)
typedef Reference<AnimatedTextureProxy> AnimatedTextureReference;

class AnimatedTextureProxy : public Proxy
{
public:
	friend class AnimatedTextureManager;
private:
	const Abstract::Texture::textureType type;
	uint32_t height;
	uint32_t width;
	uint32_t linearSize;
	uint32_t mipMapCount;
	uint32_t frameCount;
	float frameSwitchRate;
	uint32_t currentFrame;
	Abstract::sAnimatedTexture tex;
	std::string loadPath;
public:
	AnimatedTextureProxy();
	AnimatedTextureProxy(const AnimatedTextureProxy& cpy);
	AnimatedTextureProxy(const std::string& id, Abstract::Texture::textureType taipu);
	AnimatedTextureProxy(const std::string& id, Abstract::Texture::textureType taipu, const std::string& loadpath);
	uint32_t getHeight() const;
	uint32_t getWidth() const;
	uint32_t getLinearSize() const;
	uint32_t getMipMapCount() const;
	uint32_t getFrameCount() const;

	float getFrameSwitchRate() const;
	uint32_t getCurrentFrame() const;
	void setFrameSwitchRate(float newrate);
	void setCurrentFrame(uint32_t newFrame);

	std::string& getLoadPath();
	void setLoadPath(const std::string& newPath);
	const Abstract::sAnimatedTexture getTexture() const;
};

class AnimatedTextureManager : public ResourceManager
{
public:
	friend class AnimatedTextureProxy;
	typedef MapTrait<AnimatedTextureProxy,std::string> AnimatedTextureMap;
	typedef AnimatedTextureMap::HashIterator AnimatedTextureIterator;
private:
	AnimatedTextureMap texmp;
public:
	AnimatedTextureManager() = default;
	~AnimatedTextureManager() = default;
	void updateTextures(const STime& time);
	AnimatedTextureReference query(const AnimatedTextureProxy& proxy);
	AnimatedTextureReference query(const std::string& key);
	AnimatedTextureReference commit(const AnimatedTextureProxy& proxy);

};

#endif // PROXYANIMATEDTEXTURE_HPP
