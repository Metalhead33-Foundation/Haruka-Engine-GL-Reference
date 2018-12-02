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
	: compilationStatus(GL_FALSE)
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
void ShaderProgram::bindTexture(int location, Abstract::sTexture tex)
{
	if(tex)
	{
		tex->bindTextureSide();
		glUniform1i(location, boundTextures);
		++boundTextures;
	}
}
void ShaderProgram::bindTexture(int location, Abstract::sFramebuffer tex)
{
	if(tex)
	{
		tex->bindTextureSide();
		glUniform1i(location, boundTextures);
		++boundTextures;
	}
}
void ShaderProgram::bindTexture(int location, Abstract::sFont tex)
{
	if(tex)
	{
		tex->bindTextureSide();
		glUniform1i(location, boundTextures);
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
	glGetProgramiv(shaderID, GL_LINK_STATUS, &compilationStatus);
	return true;
}

void ShaderProgram::setBool(int location, bool value) const
{
	if(location != -1) glUniform1i(location, (int)value);
}
void ShaderProgram::setInt(int location, int value) const
{
	if(location != -1) glUniform1i(location, value);
}
void ShaderProgram::setFloat(int location, float value) const
{
	if(location != -1) glUniform1f(location, value);
}
void ShaderProgram::setVec2(int location, const glm::vec2 &value) const
{
	if(location != -1) glUniform2fv(location, 1, &value[0]);
}
void ShaderProgram::setVec2(int location, float x, float y) const
{
	if(location != -1) glUniform2f(location, x, y);
}
void ShaderProgram::setVec3(int location, const glm::vec3 &value) const
{
	if(location != -1) glUniform3fv(location, 1, &value[0]);
}
void ShaderProgram::setVec3(int location, float x, float y, float z) const
{
	if(location != -1) glUniform3f(location, x, y, z);
}
void ShaderProgram::setVec4(int location, const glm::vec4 &value) const
{
	if(location != -1) glUniform4fv(location, 1, &value[0]);
}
void ShaderProgram::setVec4(int location, float x, float y, float z, float w) const
{
	if(location != -1) glUniform4f(location, x, y, z, w);
}
void ShaderProgram::setBvec2(int location, const glm::bvec2 &value) const
{
	if(location != -1) glUniform2i(location, value.x, value.y);
}
void ShaderProgram::setBvec2(int location, bool x, bool y) const
{
	if(location != -1) glUniform2i(location, x, y);
}
void ShaderProgram::setBvec3(int location, const glm::bvec3 &value) const
{
	if(location != -1) glUniform3i(location, value.x, value.y, value.z);
}
void ShaderProgram::setBvec3(int location, bool x, bool y, bool z) const
{
	if(location != -1) glUniform3i(location, x, y, z);
}
void ShaderProgram::setBvec4(int location, const glm::bvec4 &value) const
{
	if(location != -1) glUniform4i(location, value.x, value.y, value.z, value.w);
}
void ShaderProgram::setBvec4(int location, bool x, bool y, bool z, bool w) const
{
	if(location != -1) glUniform4i(location, x, y, z, w);
}
void ShaderProgram::setIvec2(int location, const glm::ivec2 &value) const
{
	if(location != -1) glUniform2iv(location, 1, &value[0]);
}
void ShaderProgram::setIvec2(int location, int x, int y) const
{
	if(location != -1) glUniform2i(location, x, y);
}
void ShaderProgram::setIvec3(int location, const glm::ivec3 &value) const
{
	if(location != -1) glUniform3iv(location, 1, &value[0]);
}
void ShaderProgram::setIvec3(int location, int x, int y, int z) const
{
	if(location != -1) glUniform3i(location, x, y, z);
}
void ShaderProgram::setIvec4(int location, const glm::ivec4 &value) const
{
	if(location != -1) glUniform4iv(location, 1, &value[0]);
}
void ShaderProgram::setIvec4(int location, int x, int y, int z, int w) const
{
	if(location != -1) glUniform4i(location, x, y, z, w);
}
void ShaderProgram::setMat2(int location, const glm::mat2 &mat) const
{
	if(location != -1) glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
}
void ShaderProgram::setMat3(int location, const glm::mat3 &mat) const
{
	if(location != -1) glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
}
void ShaderProgram::setMat4(int location, const glm::mat4 &mat) const
{
	if(location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void ShaderProgram::setBoolArray(int location, const bool *value, size_t count) const
{
	if(location == -1) return;
	std::vector<int> tmp(count);
	for(size_t i = 0; i < count;++i) tmp[i] = value[i];
	glUniform1iv(location,count,tmp.data());
}
void ShaderProgram::setIntArray(int location, const int *value, size_t count) const
{
	if(location != -1) glUniform1iv(location,count,value);
}
void ShaderProgram::setFloatArray(int location, const float *value, size_t count) const
{
	if(location != -1) glUniform1fv(location,count,value);
}
void ShaderProgram::setVec2Array(int location, const glm::vec2 *value, size_t count) const
{
	if(location != -1) glUniform2fv(location,count,&value[0][0] );
}
void ShaderProgram::setVec3Array(int location, const glm::vec3 *value, size_t count) const
{
	if(location != -1) glUniform3fv(location,count,&value[0][0]);
}
void ShaderProgram::setVec4Array(int location, const glm::vec4 *value, size_t count) const
{
	if(location != -1) glUniform4fv(location,count,&value[0][0]);
}
void ShaderProgram::setIvec2Array(int location, const glm::ivec2 *value, size_t count) const
{
	if(location != -1) glUniform2iv(location,count,&value[0][0] );
}
void ShaderProgram::setIvec3Array(int location, const glm::ivec3 *value, size_t count) const
{
	if(location != -1) glUniform3iv(location,count,&value[0][0] );
}
void ShaderProgram::setIvec4Array(int location, const glm::ivec4 *value, size_t count) const
{
	if(location != -1) glUniform4iv(location,count,&value[0][0] );
}
void ShaderProgram::setBvec2Array(int location, const glm::bvec2 *value, size_t count) const
{
	if(location == -1) return;
	std::vector<glm::ivec2> tmp(count);
	for(size_t i = 0; i < count;++i) tmp[i] = value[i];
	glUniform2iv(location,count,&tmp[0][0]);
}
void ShaderProgram::setBvec3Array(int location, const glm::bvec3 *value, size_t count) const
{
	if(location == -1) return;
	std::vector<glm::ivec3> tmp(count);
	for(size_t i = 0; i < count;++i) tmp[i] = value[i];
	glUniform3iv(location,count,&tmp[0][0]);
}
void ShaderProgram::setBvec4Array(int location, const glm::bvec4 *value, size_t count) const
{
	if(location == -1) return;
	std::vector<glm::ivec4> tmp(count);
	for(size_t i = 0; i < count;++i) tmp[i] = value[i];
	glUniform4iv(location,count,&tmp[0][0]);
}
void ShaderProgram::setMat2Array(int location, const glm::mat2 *mat, size_t count) const
{
	if(location == -1) return;
	glUniformMatrix2fv(location, count, GL_FALSE, &mat[0][0][0]);
}
void ShaderProgram::setMat3Array(int location, const glm::mat3 *mat, size_t count) const
{
	if(location != -1) glUniformMatrix3fv(location, count, GL_FALSE, &mat[0][0][0]);
}
void ShaderProgram::setMat4Array(int location, const glm::mat4 *mat, size_t count) const
{
	if(location != -1) glUniformMatrix4fv(location, count, GL_FALSE, &mat[0][0][0]);
}
int ShaderProgram::getLocation(const char* name) const
{
	return glGetUniformLocation(shaderID, name);
}
bool ShaderProgram::isValid() const
{
	return compilationStatus == GL_TRUE;
}


}
