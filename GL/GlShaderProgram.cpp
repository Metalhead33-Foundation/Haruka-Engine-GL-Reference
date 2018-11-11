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
void ShaderProgram::setBvec2(const char* name, const glm::bvec2 &value) const
{
	glUniform2i(glGetUniformLocation(shaderID, name), value.x, value.y);
}
void ShaderProgram::setBvec2(const char* name, bool x, bool y) const
{
	glUniform2i(glGetUniformLocation(shaderID, name), x, y);
}
void ShaderProgram::setBvec3(const char* name, const glm::bvec3 &value) const
{
	glUniform3i(glGetUniformLocation(shaderID, name), value.x, value.y, value.z);
}
void ShaderProgram::setBvec3(const char* name, bool x, bool y, bool z) const
{
	glUniform3i(glGetUniformLocation(shaderID, name), x, y, z);
}
void ShaderProgram::setBvec4(const char* name, const glm::bvec4 &value) const
{
	glUniform4i(glGetUniformLocation(shaderID, name), value.x, value.y, value.z, value.w);
}
void ShaderProgram::setBvec4(const char* name, bool x, bool y, bool z, bool w) const
{
	glUniform4i(glGetUniformLocation(shaderID, name), x, y, z, w);
}
void ShaderProgram::setIvec2(const char* name, const glm::ivec2 &value) const
{
	glUniform2iv(glGetUniformLocation(shaderID, name), 1, &value[0]);
}
void ShaderProgram::setIvec2(const char* name, int x, int y) const
{
	glUniform2i(glGetUniformLocation(shaderID, name), x, y);
}
void ShaderProgram::setIvec3(const char* name, const glm::ivec3 &value) const
{
	glUniform3iv(glGetUniformLocation(shaderID, name), 1, &value[0]);
}
void ShaderProgram::setIvec3(const char* name, int x, int y, int z) const
{
	glUniform3i(glGetUniformLocation(shaderID, name), x, y, z);
}
void ShaderProgram::setIvec4(const char* name, const glm::ivec4 &value) const
{
	glUniform4iv(glGetUniformLocation(shaderID, name), 1, &value[0]);
}
void ShaderProgram::setIvec4(const char* name, int x, int y, int z, int w) const
{
	glUniform4i(glGetUniformLocation(shaderID, name), x, y, z, w);
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

void ShaderProgram::setBoolArray(const char* name, const bool *value, size_t count) const
{
	std::vector<int> tmp(count);
	for(size_t i = 0; i < count;++i) tmp[i] = value[i];
	glUniform1iv(glGetUniformLocation(shaderID, name),count,tmp.data());
}
void ShaderProgram::setIntArray(const char* name, const int *value, size_t count) const
{
	glUniform1iv(glGetUniformLocation(shaderID, name),count,value);
}
void ShaderProgram::setFloatArray(const char* name, const float *value, size_t count) const
{
	glUniform1fv(glGetUniformLocation(shaderID, name),count,value);
}
void ShaderProgram::setVec2Array(const char* name, const glm::vec2 *value, size_t count) const
{
	glUniform2fv(glGetUniformLocation(shaderID, name),count,&value[0][0] );
}
void ShaderProgram::setVec3Array(const char* name, const glm::vec3 *value, size_t count) const
{
	glUniform3fv(glGetUniformLocation(shaderID, name),count,&value[0][0]);
}
void ShaderProgram::setVec4Array(const char* name, const glm::vec4 *value, size_t count) const
{
	glUniform4fv(glGetUniformLocation(shaderID, name),count,&value[0][0]);
}
void ShaderProgram::setIvec2Array(const char* name, const glm::ivec2 *value, size_t count) const
{
	glUniform2iv(glGetUniformLocation(shaderID, name),count,&value[0][0] );
}
void ShaderProgram::setIvec3Array(const char* name, const glm::ivec3 *value, size_t count) const
{
	glUniform3iv(glGetUniformLocation(shaderID, name),count,&value[0][0] );
}
void ShaderProgram::setIvec4Array(const char* name, const glm::ivec4 *value, size_t count) const
{
	glUniform4iv(glGetUniformLocation(shaderID, name),count,&value[0][0] );
}
void ShaderProgram::setBvec2Array(const char* name, const glm::bvec2 *value, size_t count) const
{
	std::vector<glm::ivec2> tmp(count);
	for(size_t i = 0; i < count;++i) tmp[i] = value[i];
	glUniform2iv(glGetUniformLocation(shaderID, name),count,&tmp[0][0]);
}
void ShaderProgram::setBvec3Array(const char* name, const glm::bvec3 *value, size_t count) const
{
	std::vector<glm::ivec3> tmp(count);
	for(size_t i = 0; i < count;++i) tmp[i] = value[i];
	glUniform3iv(glGetUniformLocation(shaderID, name),count,&tmp[0][0]);
}
void ShaderProgram::setBvec4Array(const char* name, const glm::bvec4 *value, size_t count) const
{
	std::vector<glm::ivec4> tmp(count);
	for(size_t i = 0; i < count;++i) tmp[i] = value[i];
	glUniform4iv(glGetUniformLocation(shaderID, name),count,&tmp[0][0]);
}
void ShaderProgram::setMat2Array(const char* name, const glm::mat2 *mat, size_t count) const
{
	glUniformMatrix2fv(glGetUniformLocation(shaderID, name), count, GL_FALSE, &mat[0][0][0]);
}
void ShaderProgram::setMat3Array(const char* name, const glm::mat3 *mat, size_t count) const
{
	glUniformMatrix3fv(glGetUniformLocation(shaderID, name), count, GL_FALSE, &mat[0][0][0]);
}
void ShaderProgram::setMat4Array(const char* name, const glm::mat4 *mat, size_t count) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name), count, GL_FALSE, &mat[0][0][0]);
}


}
