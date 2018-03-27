#include "GlShaderProgram.hpp"
#include <stdexcept>

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
void GlShaderProgram::linkShaders()
{
	for(ModuleIterator it = modules.begin(); it != modules.end(); ++it)
	{
		GlShaderModule* mod = dynamic_cast<GlShaderModule*>(it->get());
		if(!mod) throw std::runtime_error("Invalid shader module!");
		else glAttachShader(shaderID,mod->getShaderID());
	}
	glLinkProgram(shaderID);
}
