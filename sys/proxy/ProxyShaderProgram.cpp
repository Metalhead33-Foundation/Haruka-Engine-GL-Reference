#include "ProxyShaderProgram.hpp"
#include "../GameSystem.hpp"

ShaderProgramProxy::ShaderProgramProxy()
	: Id(""), prog(nullptr)
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
			Storage<ShaderProgramProxy> proxy = *ref;
			proxy.beginSet();
			proxy->prog = sys->getEngine()->createShaderProgram();
			if(proxy->prog) {
			for(auto it = modref.begin(); it != modref.end(); ++it)
			{
				ReadReference<ShaderModpuleProxy> read(*it);
				proxy->prog->pushModule(read->getModule());
			}
			proxy->prog->linkShaders();
			}
			proxy.endSet();
		}
	);
	return ref;
}
