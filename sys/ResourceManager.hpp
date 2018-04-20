#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include "../abstract/Global.hpp"
#include <functional>

DEFINE_CLASS(GameSystem)
DEFINE_CLASS(ResourceManager)

class ResourceManager
{
public:
	friend class GameSystem;
	typedef std::function<void(pGameSystem)> Lambda;
protected:
	static pGameSystem SYS;
	static void pushCommand(Lambda lambda);
public:
	ResourceManager();
	virtual ~ResourceManager();
};

#endif // RESOURCEMANAGER_HPP
