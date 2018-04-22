#include "ProxyShaderModule.hpp"
#include "../GameSystem.hpp"

ShaderModuleProxy::ShaderModuleProxy()
	: Proxy(""), type(Abstract::ShaderModule::COMPUTE_SHADER), mod(nullptr)
{
	;
}
ShaderModuleProxy::ShaderModuleProxy(const ShaderModuleProxy& cpy)
	: Proxy(cpy.Id), type(cpy.type), mod(cpy.mod), loadPath(cpy.loadPath)
{
	;
}
ShaderModuleProxy::ShaderModuleProxy(const std::string& id, Abstract::ShaderModule::ShaderType taipu)
	: Proxy(id), type(taipu), mod(nullptr)
{
	;
}
ShaderModuleProxy::ShaderModuleProxy(const std::string& id, Abstract::ShaderModule::ShaderType taipu,
									 const std::string& loadpath)
	: Proxy(id), type(taipu), mod(nullptr), loadPath(loadpath)
{
	;
}
std::string& ShaderModuleProxy::getLoadPath()
{
	return loadPath;
}
void ShaderModuleProxy::setLoadPath(const std::string& newPath)
{
	loadPath = newPath;
}
const Abstract::sShaderModule ShaderModuleProxy::getModule() const
{
	return mod;
}
ShaderModuleReference ShaderModuleManager::query(const std::string& key)
{
	auto it = modmp.find(key);
	ShaderModuleReference ref;
	if(it == modmp.end())
	{
		ref = ShaderModuleReference();
	}
	else
	{
		ref = it->second;
	}
	modmp.finish();
	return ref;
}
ShaderModuleReference ShaderModuleManager::query(const ShaderModuleProxy& proxy)
{
	auto it = modmp.find(proxy.Id);
	ShaderModuleReference ref;
	if(it == modmp.end())
	{
		ref = ShaderModuleReference();
	}
	else
	{
		ref = it->second;
	}
	modmp.finish();
	return ref;
}
ShaderModuleReference ShaderModuleManager::commit(const ShaderModuleProxy& proxy)
{
	auto ref = modmp.getEntry(proxy.Id, proxy.type);
	if(ref->isInitialized()) return ref;
	auto type = proxy.type;
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(proxy.loadPath);
	pushCommand(
				[ref,reedah,type](pGameSystem sys) {
			Storage<ShaderModuleProxy> &proxy = *ref;
			proxy.beginSet();
			proxy->mod = sys->getEngine()->createShaderModule(type,reedah);
			std::cout << "[SHADERS] Shader module \"" << proxy->Id << "\" initialized." << std::endl;
			proxy.endSet();
		}
	);
	return ref;
}
