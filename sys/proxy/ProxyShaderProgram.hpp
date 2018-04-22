#ifndef PROXYSHADERPROGRAM_HPP
#define PROXYSHADERPROGRAM_HPP
#include "ProxyShaderModule.hpp"
#include "../../abstract/ShaderProgram.hpp"
#include <vector>

DEFINE_CLASS(ShaderProgramProxy)
DEFINE_CLASS(ShaderProgramManager)
typedef Reference<ShaderProgramProxy> ShaderProgramReference;
class ShaderProgramProxy : public Proxy
{
public:
	friend class ShaderProgramManager;
private:
	Abstract::sShaderProgram prog;
	std::vector<ShaderModuleReference> modref;
public:
	ShaderProgramProxy();
	ShaderProgramProxy(const ShaderProgramProxy& cpy);
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
	typedef ShaderProxyMap::HashIterator ShaderIterator;
private:
	ShaderProxyMap progmp;
public:
	ShaderProgramManager() = default;
	~ShaderProgramManager() = default;
	ShaderProgramReference query(const ShaderProgramProxy& proxy);
	ShaderProgramReference query(const std::string& key);
	ShaderProgramReference commit(const ShaderProgramProxy& proxy);
};

#endif // PROXYSHADERPROGRAM_HPP
