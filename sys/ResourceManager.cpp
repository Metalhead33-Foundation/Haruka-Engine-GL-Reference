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
	std::cout << "[SYSTEM] [" << this << "] is pushing a command to [" << SYS << "]!" << std::endl;
	if(SYS) SYS->pushCommand(lambda);
	std::cout << "[SYSTEM] [" << this << "] has succesfully pushed a command to [" << SYS << "]!" << std::endl;
}
