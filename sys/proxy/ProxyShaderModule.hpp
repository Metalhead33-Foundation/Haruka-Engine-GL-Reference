#ifndef PROXYSHADERPMODULE_HPP
#define PROXYSHADERPMODULE_HPP
#include "../ResourceManager.hpp"
#include "../../abstract/ShaderModule.hpp"
#include "../../abstract/HashTrait.hpp"

DEFINE_CLASS(ShaderModuleProxy)
DEFINE_CLASS(ShaderModuleManager)
typedef Reference<ShaderModuleProxy> ShaderModuleReference;
class ShaderModuleProxy
{
public:
	friend class ShaderModuleManager;
private:
	const std::string Id;
	const Abstract::ShaderModule::ShaderType type;
	Abstract::sShaderModule mod;
	std::string loadPath;
public:
	ShaderModuleProxy();
	ShaderModuleProxy(const ShaderModuleProxy& cpy);
	ShaderModuleProxy(const std::string& id, Abstract::ShaderModule::ShaderType taipu);
	ShaderModuleProxy(const std::string& id, Abstract::ShaderModule::ShaderType taipu, const std::string& loadpath);
	std::string& getLoadPath();
	void setLoadPath(const std::string& newPath);
	const Abstract::sShaderModule getModule() const;
	const std::string& getId() const;
};

class ShaderModuleManager : public ResourceManager
{
public:
	friend class ShaderModuleProxy;
	typedef MapTrait<ShaderModuleProxy,std::string> ShaderModuleMap;
	typedef ShaderModuleMap::HashIterator ShaderModuleIterator;
private:
	ShaderModuleMap modmp;
public:
	ShaderModuleManager() = default;
	~ShaderModuleManager() = default;
	ShaderModuleReference query(const ShaderModuleProxy& proxy);
	ShaderModuleReference query(const std::string& key);
	ShaderModuleReference commit(const ShaderModuleProxy& proxy);
};

#endif // PROXYSHADERPMODULE_HPP
