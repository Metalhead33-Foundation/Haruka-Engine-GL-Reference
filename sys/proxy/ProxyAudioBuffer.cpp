#include "ProxyAudioBuffer.hpp"
#include "../GameSystem.hpp"

BufferProxy::BufferProxy()
	: Proxy(""), buff(nullptr), loadPath("")
{
	;
}
BufferProxy::BufferProxy(const BufferProxy& cpy)
	: Proxy(cpy.Id), buff(cpy.buff), loadPath(cpy.loadPath)
{
	;
}
BufferProxy::BufferProxy(const std::string& id)
	: Proxy(id), buff(nullptr), loadPath("")
{
	;
}
BufferProxy::BufferProxy(const std::string& id, const std::string& loadpath)
	: Proxy(id), buff(nullptr), loadPath(loadpath)
{
	;
}
void BufferProxy::setLoadPath(const std::string& loadpath)
{
	loadPath = loadpath;
}
const std::string& BufferProxy::getLoadPath()
{
	return loadPath;
}
const Audio::sBuffer BufferProxy::getBuffer() const
{
	return buff;
}
BufferReference BufferManager::query(const BufferProxy& proxy)
{
	auto it = buffmp.find(proxy.Id);
	BufferReference ref;
	if(it == buffmp.end())
	{
		ref = BufferReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
BufferReference BufferManager::query(const std::string& key)
{
	auto it = buffmp.find(key);
	BufferReference ref;
	if(it == buffmp.end())
	{
		ref = BufferReference();
	}
	else
	{
		ref = it->second;
	}
	buffmp.finish();
	return ref;
}
BufferReference BufferManager::commit(const BufferProxy& proxy)
{
	auto ref = buffmp.getEntry(proxy.Id);
	Abstract::sFIO readah = PhysFS::FileHandle::openRead(proxy.loadPath);
	if(ref->isInitialized()) return ref;
	pushCommand( [proxy, ref,readah ](pGameSystem sys) {
	Storage<BufferProxy> &prxy = *ref;
	prxy.beginSet();
	prxy->buff = sys->getSoundsys()->createSoundBuffer(readah);
	prxy.endSet();
	});
	return ref;
}
