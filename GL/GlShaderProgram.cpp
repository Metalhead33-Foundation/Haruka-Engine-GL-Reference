#include "GlShaderProgram.hpp"
#include <stdexcept>
namespace Gl {

Abstract::sShaderProgram ShaderProgram::createShaderProgram()
{
	return Abstract::sShaderProgram(new ShaderProgram());
}
ShaderProgram::ShaderProgram()
{
	shaderID = glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderID);
}
const GLuint& ShaderProgram::getShaderID() const
{
	return shaderID;
}
void ShaderProgram::pushModule(Abstract::sShaderModule mod)
{
	modules.push_back(mod);
}
void ShaderProgram::popModule()
{
	modules.pop_back();
}
bool ShaderProgram::linkShaders()
{
	for(ModuleIterator it = modules.begin(); it != modules.end(); ++it)
	{
		ShaderModule* mod = dynamic_cast<ShaderModule*>(it->get());
		if(!mod) return false;
		else glAttachShader(shaderID,mod->getShaderID());
	}
	glLinkProgram(shaderID);
	return true;
}

}
