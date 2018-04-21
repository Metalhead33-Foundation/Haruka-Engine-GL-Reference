#include "ProxyTexture.hpp"
#include "../GameSystem.hpp"


TextureProxy::TextureProxy()
	: Id(""), type(Abstract::Texture::texture_diffuse), tex(nullptr)
{
	;
}
TextureProxy::TextureProxy(const TextureProxy& cpy)
	: Id(cpy.Id), type(cpy.type), height(cpy.height),
	  width(cpy.width), linearSize(cpy.linearSize),
	  mipMapCount(cpy.mipMapCount), tex(cpy.tex),
	  loadPath(cpy.loadPath)
{
	;
}
TextureProxy::TextureProxy(const std::string& id, Abstract::Texture::textureType taipu)
	: Id(id), type(taipu), tex(nullptr)
{
	;
}
TextureProxy::TextureProxy(const std::string& id, Abstract::Texture::textureType taipu,
						   const std::string& loadpath)
	: Id(id), type(taipu), tex(nullptr), loadPath(loadpath)
{
	;
}
uint32_t TextureProxy::getHeight() const
{
	return height;
}
uint32_t TextureProxy::getWidth() const
{
	return width;
}
uint32_t TextureProxy::getLinearSize() const
{
	return linearSize;
}
uint32_t TextureProxy::getMipMapCount() const
{
	return mipMapCount;
}
std::string& TextureProxy::getLoadPath()
{
	return loadPath;
}
void TextureProxy::setLoadPath(const std::string& newPath)
{
	loadPath = newPath;
}
const Abstract::sTexture TextureProxy::getTexture() const
{
	return tex;
}
const std::string& TextureProxy::getId() const
{
	return Id;
}
TextureReference TextureManager::query(const std::string& key)
{
	auto it = texmp.find(key);
	TextureReference ref;
	if(it == texmp.end())
	{
		ref = TextureReference();
	}
	else
	{
		ref = it->second;
	}
	texmp.finish();
	return ref;
}
TextureReference TextureManager::query(const TextureProxy& proxy)
{
	auto it = texmp.find(proxy.Id);
	TextureReference ref;
	if(it == texmp.end())
	{
		ref = TextureReference();
	}
	else
	{
		ref = it->second;
	}
	texmp.finish();
	return ref;
}

TextureReference TextureManager::commit(const TextureProxy& proxy)
{
	auto ref = texmp.getEntry(proxy.Id, proxy.type);
	if(ref->isInitialized()) return ref;
	auto type = proxy.type;
	bool isDDS = false;
	std::string lastFour = proxy.loadPath.substr( proxy.loadPath.length() - 4);
	if(lastFour == ".dds" || lastFour == ".DDS") isDDS = true;
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(proxy.loadPath);
	pushCommand(
				[ref,reedah,type,isDDS](pGameSystem sys) {
			Storage<TextureProxy> &proxy = *ref;
			proxy.beginSet();
			if(isDDS) proxy->tex = sys->getEngine()->createTextureFromDDS(type,reedah);
			else  proxy->tex = sys->getEngine()->createTextureFromImage(type,reedah);
			if(proxy->tex) {
			proxy->height = proxy->tex->getHeight();
			proxy->width = proxy->tex->getWidth();
			proxy->linearSize = proxy->tex->getLinearSize();
			proxy->mipMapCount = proxy->tex->getMipMapCount();
			}
			std::cout << "[TEXTURES] Texture \"" << proxy->Id << "\" initialized." << std::endl;
			proxy.endSet();
		}
	);
	return ref;
}
