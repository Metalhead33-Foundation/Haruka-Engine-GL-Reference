#include "ProxyAnimatedTexture.hpp"
#include "../GameSystem.hpp"

AnimatedTextureProxy::AnimatedTextureProxy()
	: Proxy(""), type(Abstract::Texture::texture_diffuse),
	  height(0), width(0), linearSize(0), mipMapCount(0),
	  frameCount(0), frameSwitchRate(0.0f), currentFrame(0),
	  tex(nullptr), loadPath("")
{
	;
}
AnimatedTextureProxy::AnimatedTextureProxy(const AnimatedTextureProxy& cpy)
	: Proxy(cpy.Id), type(cpy.type),
	height(cpy.height), width(cpy.width), linearSize(cpy.linearSize),
	mipMapCount(cpy.mipMapCount), frameCount(cpy.frameCount),
	frameSwitchRate(cpy.frameSwitchRate), currentFrame(cpy.currentFrame),
	tex(cpy.tex), loadPath(cpy.loadPath)
{
	;
}
AnimatedTextureProxy::AnimatedTextureProxy(const std::string& id, Abstract::Texture::textureType taipu)
	: Proxy(id), type(taipu), tex(nullptr), loadPath("")
{
	;
}
AnimatedTextureProxy::AnimatedTextureProxy(const std::string& id, Abstract::Texture::textureType taipu, const std::string& loadpath)
	: Proxy(id), type(taipu), tex(nullptr), loadPath(loadpath)
{
	;
}
uint32_t AnimatedTextureProxy::getHeight() const
{
	return height;
}
uint32_t AnimatedTextureProxy::getWidth() const
{
	return width;
}
uint32_t AnimatedTextureProxy::getLinearSize() const
{
	return linearSize;
}
uint32_t AnimatedTextureProxy::getMipMapCount() const
{
	return mipMapCount;
}
uint32_t AnimatedTextureProxy::getFrameCount() const
{
	return frameCount;
}

float AnimatedTextureProxy::getFrameSwitchRate() const
{
	return frameSwitchRate;
}
uint32_t AnimatedTextureProxy::getCurrentFrame() const
{
	return currentFrame;
}
void AnimatedTextureProxy::setFrameSwitchRate(float newrate)
{
	frameSwitchRate = newrate;
}
void AnimatedTextureProxy::setCurrentFrame(uint32_t newFrame)
{
	currentFrame = newFrame;
}

std::string& AnimatedTextureProxy::getLoadPath()
{
	return loadPath;
}
void AnimatedTextureProxy::setLoadPath(const std::string& newPath)
{
	loadPath = newPath;
}
const Abstract::sAnimatedTexture AnimatedTextureProxy::getTexture() const
{
	return tex;
}

void AnimatedTextureManager::updateTextures(const STime& time)
{
	for(auto it = texmp.begin(); it != texmp.end(); ++it)
	{
		if(it->second && it->second->isInitialized()) {
		it->second->beginSet();
		if((*it->second)->getTexture())
		{
			(*it->second)->getTexture()->goForward(time.getSeconds());
		}
		it->second->endSet();
		}
	}
	texmp.finish();
}
AnimatedTextureReference AnimatedTextureManager::query(const std::string& key)
{
	auto it = texmp.find(key);
	AnimatedTextureReference ref;
	if(it == texmp.end())
	{
		ref = AnimatedTextureReference();
	}
	else
	{
		ref = it->second;
	}
	texmp.finish();
	return ref;
}
AnimatedTextureReference AnimatedTextureManager::query(const AnimatedTextureProxy& proxy)
{
	auto it = texmp.find(proxy.Id);
	AnimatedTextureReference ref;
	if(it == texmp.end())
	{
		ref = AnimatedTextureReference();
	}
	else
	{
		ref = it->second;
	}
	texmp.finish();
	return ref;
}

AnimatedTextureReference AnimatedTextureManager::commit(const AnimatedTextureProxy& proxy)
{
	auto ref = texmp.getEntry(proxy.Id, proxy.type);
	if(ref->isInitialized()) return ref;
	auto type = proxy.type;
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(proxy.loadPath);
	pushCommand(
				[ref,reedah,type](pGameSystem sys) {
			Storage<AnimatedTextureProxy> &proxy = *ref;
			proxy.beginSet();
			proxy->tex = sys->getEngine()->createTextureFromGIF(type,reedah);
			if(proxy->tex) {
			// proxy->tex->setFrameSwitchRate(proxy->frameSwitchRate);
			proxy->height = proxy->tex->getHeight();
			proxy->width = proxy->tex->getWidth();
			proxy->linearSize = proxy->tex->getLinearSize();
			proxy->mipMapCount = proxy->tex->getMipMapCount();
			proxy->currentFrame = proxy->tex->getCurrentFrame();
			}
			std::cout << "[TEXTURES] Texture \"" << proxy->Id << "\" initialized." << std::endl;
			proxy.endSet();
		}
	);
	return ref;
}
