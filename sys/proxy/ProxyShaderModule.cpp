#include "ProxyShaderModule.hpp"
#include "../GameSystem.hpp"

ShaderModpuleProxy::ShaderModpuleProxy()
	: Id(""), type(Abstract::ShaderModule::COMPUTE_SHADER), mod(nullptr)
{
	;
}
ShaderModpuleProxy::ShaderModpuleProxy(const ShaderModpuleProxy& cpy)
	: Id(cpy.Id), type(cpy.type), mod(cpy.mod), loadPath(cpy.loadPath)
{
	;
}
ShaderModpuleProxy::ShaderModpuleProxy(const std::string& id, Abstract::ShaderModule::ShaderType taipu)
	: Id(id), type(taipu), mod(nullptr)
{
	;
}
std::string& ShaderModpuleProxy::getLoadPath()
{
	return loadPath;
}
void ShaderModpuleProxy::setLoadPath(const std::string& newPath)
{
	loadPath = newPath;
}
const Abstract::sShaderModule ShaderModpuleProxy::getModule() const
{
	return mod;
}
ShaderModuleReference ShaderModuleManager::query(const ShaderModpuleProxy& proxy)
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
ShaderModuleReference ShaderModuleManager::commit(const ShaderModpuleProxy& proxy)
{
	auto ref = modmp.getEntry(proxy.Id, proxy.type);
	if(ref->isInitialized()) return ref;
	auto type = proxy.type;
	Abstract::sFIO reedah = PhysFS::FileHandle::openRead(proxy.loadPath);
	pushCommand(
				[ref,reedah,type](pGameSystem sys) {
			Storage<ShaderModpuleProxy> &proxy = *ref;
			proxy.beginSet();
			proxy->mod = sys->getEngine()->createShaderModule(type,reedah);
			proxy.endSet();
		}
	);
	return ref;
}
