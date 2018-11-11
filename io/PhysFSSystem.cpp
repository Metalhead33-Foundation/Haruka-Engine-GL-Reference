#include "PhysFSSystem.hpp"
#include "PhysFsFileHandle.hpp"
namespace PhysFS {
PhysFSSystem::PhysFSSystem()
{

}
Abstract::sFIO PhysFSSystem::openRead(const std::string& path)
{
	return FileHandle::openRead(path);
}
Abstract::sFIO PhysFSSystem::openWrite(const std::string& path)
{
	return FileHandle::openWrite(path);
}
bool PhysFSSystem::exists(const std::string& path)
{
	return PHYSFS_exists(path.c_str());
}
Abstract::byteBuffer PhysFSSystem::loadFileIntoBuffer(const std::string &path)
{
	return FileHandle::loadFileIntoBuffer(path);
}
std::string PhysFSSystem::stringizeFile(const std::string &path)
{
	return FileHandle::stringizeFile(path);
}
}
