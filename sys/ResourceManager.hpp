#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include "../abstract/Global.hpp"
#include <functional>

DEFINE_CLASS(GameSystem)
DEFINE_CLASS(ResourceManager)
DEFINE_CLASS(Proxy)

class Proxy
{
public:
	friend class ResourceManager;
protected:
	const std::string Id;
public:
	Proxy(const std::string& id);
	virtual ~Proxy() = default;
	const std::string& getId() const;
};

class ResourceManager
{
public:
	friend class GameSystem;
	friend class Proxy;
	typedef std::function<void(pGameSystem)> Lambda;
protected:
	static pGameSystem SYS;
	void pushCommand(Lambda lambda);
public:
	ResourceManager();
	virtual ~ResourceManager();
};

#endif // RESOURCEMANAGER_HPP
