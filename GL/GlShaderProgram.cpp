#include "GlShaderProgram.hpp"
#include "GlTexture.hpp"
#include "GlFont.hpp"
#include "GlFramebuffer.hpp"
#include <stdexcept>
namespace Gl {

GLuint ShaderProgram::lastUsedId = 0;
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
void ShaderProgram::useShader()
{
	if(lastUsedId != shaderID)
	{
		glUseProgram(shaderID);
		lastUsedId = shaderID;
	}
	boundTextures = 0;
}
void ShaderProgram::bindTexture()
{
	glUniform1i(glGetUniformLocation(shaderID, Texture::TEX_TYPES[Texture::texture_diffuse]), boundTextures);
	++boundTextures;
}
void ShaderProgram::bindTexture(Abstract::sTexture tex)
{
	if(tex)
	{
		tex->bindTextureSide();
		glUniform1i(glGetUniformLocation(shaderID, tex->stringizeType()), boundTextures);
		++boundTextures;
	}
}
void ShaderProgram::bindTexture(Abstract::sFramebuffer tex)
{
	if(tex)
	{
		tex->bindTextureSide();
		glUniform1i(glGetUniformLocation(shaderID, tex->stringizeType()), boundTextures);
		++boundTextures;
	}
}
void ShaderProgram::bindTexture(Abstract::sFont tex)
{
	if(tex)
	{
		tex->bindTextureSide();
		glUniform1i(glGetUniformLocation(shaderID, tex->stringizeType()), boundTextures);
		++boundTextures;
	}
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

void ShaderProgram::setBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name), (int)value);
}
void ShaderProgram::setInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name), value);
}
void ShaderProgram::setFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderID, name), value);
}
void ShaderProgram::setVec2(const char* name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(shaderID, name), 1, &value[0]);
}
void ShaderProgram::setVec2(const char* name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(shaderID, name), x, y);
}
void ShaderProgram::setVec3(const char* name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(shaderID, name), 1, &value[0]);
}
void ShaderProgram::setVec3(const char* name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(shaderID, name), x, y, z);
}
void ShaderProgram::setVec4(const char* name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(shaderID, name), 1, &value[0]);
}
void ShaderProgram::setVec4(const char* name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(shaderID, name), x, y, z, w);
}
void ShaderProgram::setMat2(const char* name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, &mat[0][0]);
}
void ShaderProgram::setMat3(const char* name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, &mat[0][0]);
}
void ShaderProgram::setMat4(const char* name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, &mat[0][0]);
}

}
