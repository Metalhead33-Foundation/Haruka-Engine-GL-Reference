#include "ProxyShaderProgram.hpp"
#include "../GameSystem.hpp"

ShaderProgramProxy::ShaderProgramProxy()
	: Id(""), prog(nullptr)
{
	;
}
ShaderProgramProxy::ShaderProgramProxy(const ShaderProgramProxy& cpy)
	: Id(cpy.Id), modref(cpy.modref), prog(cpy.prog)
{
	;
}
ShaderProgramProxy::ShaderProgramProxy(const std::string& id)
	: Id(id), prog(nullptr)
{
	;
}
void ShaderProgramProxy::addModule(ShaderModuleReference mod)
{
	modref.push_back(mod);
}
void ShaderProgramProxy::removeModule(ShaderModuleReference mod)
{
	for(auto it = modref.begin(); it != modref.end();++it)
	{
		if(*it == mod)
		{
			modref.erase(it);
			break;
		}
	}
}
const Abstract::sShaderProgram ShaderProgramProxy::getProgram() const
{
	return prog;
}
const std::string& ShaderProgramProxy::getId() const
{
	return Id;
}
ShaderProgramReference ShaderProgramManager::query(const std::string& key)
{
	auto it = progmp.find(key);
	ShaderProgramReference ref;
	if(it == progmp.end())
	{
		ref = ShaderProgramReference();
	}
	else
	{
		ref = it->second;
	}
	progmp.finish();
	return ref;
}
ShaderProgramReference ShaderProgramManager::query(const ShaderProgramProxy& proxy)
{
	auto it = progmp.find(proxy.Id);
	ShaderProgramReference ref;
	if(it == progmp.end())
	{
		ref = ShaderProgramReference();
	}
	else
	{
		ref = it->second;
	}
	progmp.finish();
	return ref;
}
ShaderProgramReference ShaderProgramManager::commit(const ShaderProgramProxy& proxy)
{
	auto ref = progmp.getEntry(proxy.Id);
	std::vector<ShaderModuleReference> modref = proxy.modref;
	if(ref->isInitialized()) return ref;
	pushCommand(
				[ref,modref](pGameSystem sys) {
			Storage<ShaderProgramProxy> &proxy = *ref;
			proxy.beginSet();
			proxy->prog = sys->getEngine()->createShaderProgram();
			if(proxy->prog) {
			for(auto it = modref.begin(); it != modref.end(); ++it)
			{
				ReadReference<ShaderModuleProxy> read(*it);
				std::cout << "[SHADERS] Attaching module " << read->getId() << " to " << proxy->Id << "." << std::endl;
				proxy->prog->pushModule(read->getModule());
			}
			std::cout << "[SHADERS] Linking shader program \"" << proxy->Id << "\"." << std::endl;
			proxy->prog->linkShaders();
			std::cout << "[SHADERS] Shader program \"" << proxy->Id << "\" initialized." << std::endl;
			}
			proxy.endSet();
		}
	);
	return ref;
}
