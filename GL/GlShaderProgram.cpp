#include "GlShaderProgram.hpp"
#include <stdexcept>

sShaderProgram GlShaderProgram::createShaderProgram()
{
	return sShaderProgram(new GlShaderProgram());
}
GlShaderProgram::GlShaderProgram()
{
	shaderID = glCreateProgram();
}
GlShaderProgram::~GlShaderProgram()
{
	glDeleteProgram(shaderID);
}
const GLuint& GlShaderProgram::getShaderID() const
{
	return shaderID;
}
void GlShaderProgram::pushModule(sShaderModule mod)
{
	modules.push_back(mod);
}
void GlShaderProgram::popModule()
{
	modules.pop_back();
}
bool GlShaderProgram::linkShaders()
{
	for(ModuleIterator it = modules.begin(); it != modules.end(); ++it)
	{
		GlShaderModule* mod = dynamic_cast<GlShaderModule*>(it->get());
		if(!mod) return false;
		else glAttachShader(shaderID,mod->getShaderID());
	}
	glLinkProgram(shaderID);
	return true;
}
