#ifndef PROXYSHADERPROGRAM_HPP
#define PROXYSHADERPROGRAM_HPP
#include "ProxyShaderModule.hpp"
#include "../../abstract/ShaderProgram.hpp"
#include <vector>

DEFINE_CLASS(ShaderProgramProxy)
DEFINE_CLASS(ShaderProgramManager)
typedef Reference<ShaderProgramProxy> ShaderProgramReference;
class ShaderProgramProxy
{
public:
	friend class ShaderProgramManager;
private:
	const std::string Id;
	Abstract::sShaderProgram prog;
	std::vector<ShaderModuleReference> modref;
public:
	ShaderProgramProxy();
	ShaderProgramProxy(const std::string& id);
	void addModule(ShaderModuleReference mod);
	void removeModule(ShaderModuleReference mod);
	const Abstract::sShaderProgram getProgram() const;
};

class ShaderProgramManager : public ResourceManager
{
public:
	friend class ShaderProgramProxy;
	typedef MapTrait<ShaderProgramProxy,std::string> ShaderProxyMap;
	typedef ShaderProxyMap::iterator ShaderIterator;
private:
	ShaderProxyMap progmp;
public:
	ShaderProgramManager();
	~ShaderProgramManager();
	ShaderProgramReference query(const ShaderProgramProxy& proxy);
	ShaderProgramReference commit(const ShaderProgramProxy& proxy);
};

#endif // PROXYSHADERPROGRAM_HPP
