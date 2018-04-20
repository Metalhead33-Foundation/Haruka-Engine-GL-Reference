#ifndef PROXYTEXTURE_HPP
#define PROXYTEXTURE_HPP
#include "../ResourceManager.hpp"
#include "../../abstract/Texture.hpp"
#include "../../abstract/HashTrait.hpp"

DEFINE_CLASS(TextureProxy)
DEFINE_CLASS(TextureManager)
typedef Reference<TextureProxy> TextureReference;

class TextureProxy
{
public:
	friend class TextureManager;
private:
	const std::string Id;
	const Abstract::Texture::textureType type;
	uint32_t height;
	uint32_t width;
	uint32_t linearSize;
	uint32_t mipMapCount;
	Abstract::sTexture tex;
	std::string loadPath;
public:
	TextureProxy();
	TextureProxy(const std::string& id, Abstract::Texture::textureType taipu);
	uint32_t getHeight() const;
	uint32_t getWidth() const;
	uint32_t getLinearSize() const;
	uint32_t getMipMapCount() const;
	std::string& getLoadPath();
	void setLoadPath(const std::string& newPath);
	const Abstract::sTexture getTexture() const;
};

class TextureManager : public ResourceManager
{
public:
	friend class TextureProxy;
	typedef MapTrait<TextureProxy,std::string> TextureMap;
	typedef TextureMap::iterator TextureIterator;
private:
	TextureMap texmp;
public:
	TextureManager();
	~TextureManager();
	TextureReference query(const TextureProxy& proxy);
	TextureReference commit(const TextureProxy& proxy);

};

#endif // PROXYTEXTURE_HPP
