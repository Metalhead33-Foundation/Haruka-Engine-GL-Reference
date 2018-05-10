#ifndef PHYSFSSYSTEM_HPP
#define PHYSFSSYSTEM_HPP
#include "../abstract/FIOSys.hpp"
namespace PhysFS {
class PhysFSSystem : public Abstract::FIOSys
{
public:
	PhysFSSystem();
	Abstract::sFIO openRead(const std::string& path);
	Abstract::sFIO openWrite(const std::string& path);
	bool exists(const std::string& path);
};
}
#endif // PHYSFSSYSTEM_HPP
