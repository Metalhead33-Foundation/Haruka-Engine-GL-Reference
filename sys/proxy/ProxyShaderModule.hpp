#ifndef PROXYSHADERPMODULE_HPP
#define PROXYSHADERPMODULE_HPP
#include "../ResourceManager.hpp"
#include "../../abstract/ShaderModule.hpp"
#include "../../abstract/HashTrait.hpp"

DEFINE_CLASS(ShaderModpuleProxy)
DEFINE_CLASS(ShaderModuleManager)
typedef Reference<ShaderModpuleProxy> ShaderModuleReference;
class ShaderModpuleProxy
{
public:
	friend class ShaderModuleManager;
private:
	const std::string Id;
	const Abstract::ShaderModule::ShaderType type;
	Abstract::sShaderModule mod;
	std::string loadPath;
public:
	ShaderModpuleProxy();
	ShaderModpuleProxy(const std::string& id, Abstract::ShaderModule::ShaderType taipu);
	std::string& getLoadPath();
	void setLoadPath(const std::string& newPath);
	const Abstract::sShaderModule getModule() const;
};

class ShaderModuleManager : public ResourceManager
{
public:
	friend class ShaderModpuleProxy;
	typedef MapTrait<ShaderModpuleProxy,std::string> ShaderModuleMap;
	typedef ShaderModuleMap::iterator ShaderModuleIterator;
private:
	ShaderModuleMap modmp;
public:
	ShaderModuleManager();
	~ShaderModuleManager();
	ShaderModuleReference query(const ShaderModpuleProxy& proxy);
	ShaderModuleReference commit(const ShaderModpuleProxy& proxy);
};

#endif // PROXYSHADERPMODULE_HPP
