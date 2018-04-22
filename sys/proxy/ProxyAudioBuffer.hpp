#ifndef PROXYAUDIOBUFFER_HPP
#define PROXYAUDIOBUFFER_HPP
#include "../ResourceManager.hpp"
#include "../../audio/Audio.hpp"
#include "../../abstract/HashTrait.hpp"

DEFINE_CLASS(BufferProxy)
DEFINE_CLASS(BufferManager)
typedef Reference<BufferProxy> BufferReference;

class BufferProxy : public Proxy
{
public:
	friend class BufferManager;
private:
	Audio::sBuffer buff;
	std::string loadPath;
public:
	BufferProxy();
	BufferProxy(const BufferProxy& cpy);
	BufferProxy(const std::string& id);
	BufferProxy(const std::string& id, const std::string& loadpath);
	void setLoadPath(const std::string& loadpath);
	const std::string& getLoadPath();
	const Audio::sBuffer getBuffer() const;
};

class BufferManager : public ResourceManager
{
public:
	friend class BufferProxy;
	typedef MapTrait<BufferProxy,std::string> BufferMap;
	typedef BufferMap::HashIterator BufferIterator;
private:
	BufferMap buffmp;
public:
	BufferManager() = default;
	~BufferManager() = default;
	BufferReference query(const BufferProxy& proxy);
	BufferReference query(const std::string& key);
	BufferReference commit(const BufferProxy& proxy);
};

#endif // PROXYAUDIOBUFFER_HPP
