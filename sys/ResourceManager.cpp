#include "ResourceManager.hpp"
#include "GameSystem.hpp"

pGameSystem ResourceManager::SYS = nullptr;
ResourceManager::ResourceManager()
{
	;
}
ResourceManager::~ResourceManager()
{
	;
}
void ResourceManager::pushCommand(Lambda lambda)
{
	if(SYS) SYS->pushCommand(lambda);
}
