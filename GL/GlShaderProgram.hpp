#ifndef GLSHADERPROGRAM_HPP
#define GLSHADERPROGRAM_HPP
#include "../abstract/ShaderProgram.hpp"
#include "GlShaderModule.hpp"
#include <deque>
namespace Gl {

DEFINE_CLASS(Texture)
DEFINE_CLASS(ShaderProgram)
class ShaderProgram : public Abstract::ShaderProgram
{
public:
	friend class Texture;
	typedef std::deque<Abstract::sShaderModule> ModuleVector;
	typedef ModuleVector::iterator ModuleIterator;
private:
	GLuint shaderID;
	GLint boundTextures;
	static GLuint lastUsedId;
	ModuleVector modules;
	ShaderProgram();
public:
	static Abstract::sShaderProgram createShaderProgram();
	~ShaderProgram();
	void pushModule(Abstract::sShaderModule mod);
	void popModule();
	bool linkShaders();
	void useShader();
	const GLuint& getShaderID() const;
	virtual void setBool(const char* name, bool value) const;
	virtual void setInt(const char* name, int value) const;
	virtual void setFloat(const char* name, float value) const;
	virtual void setBvec2(const char* name, const glm::bvec2 &value) const;
	virtual void setBvec2(const char* name, bool x, bool y) const;
	virtual void setBvec3(const char* name, const glm::bvec3 &value) const;
	virtual void setBvec3(const char* name, bool x, bool y, bool z) const;
	virtual void setBvec4(const char* name, const glm::bvec4 &value) const;
	virtual void setBvec4(const char* name, bool x, bool y, bool z, bool w) const;
	virtual void setIvec2(const char* name, const glm::ivec2 &value) const;
	virtual void setIvec2(const char* name, int x, int y) const;
	virtual void setIvec3(const char* name, const glm::ivec3 &value) const;
	virtual void setIvec3(const char* name, int x, int y, int z) const;
	virtual void setIvec4(const char* name, const glm::ivec4 &value) const;
	virtual void setIvec4(const char* name, int x, int y, int z, int w) const;
	virtual void setVec2(const char* name, const glm::vec2 &value) const;
	virtual void setVec2(const char* name, float x, float y) const;
	virtual void setVec3(const char* name, const glm::vec3 &value) const;
	virtual void setVec3(const char* name, float x, float y, float z) const;
	virtual void setVec4(const char* name, const glm::vec4 &value) const;
	virtual void setVec4(const char* name, float x, float y, float z, float w) const;
	virtual void setMat2(const char* name, const glm::mat2 &mat) const;
	virtual void setMat3(const char* name, const glm::mat3 &mat) const;
	virtual void setMat4(const char* name, const glm::mat4 &mat) const;

	virtual void setBoolArray(const char* name, const bool *value, size_t count) const;
	virtual void setIntArray(const char* name, const int *value, size_t count) const;
	virtual void setFloatArray(const char* name, const float *value, size_t count) const;
	virtual void setBvec2Array(const char* name, const glm::bvec2 *value, size_t count) const;
	virtual void setBvec3Array(const char* name, const glm::bvec3 *value, size_t count) const;
	virtual void setBvec4Array(const char* name, const glm::bvec4 *value, size_t count) const;
	virtual void setIvec2Array(const char* name, const glm::ivec2 *value, size_t count) const;
	virtual void setIvec3Array(const char* name, const glm::ivec3 *value, size_t count) const;
	virtual void setIvec4Array(const char* name, const glm::ivec4 *value, size_t count) const;
	virtual void setVec2Array(const char* name, const glm::vec2 *value, size_t count) const;
	virtual void setVec3Array(const char* name, const glm::vec3 *value, size_t count) const;
	virtual void setVec4Array(const char* name, const glm::vec4 *value, size_t count) const;
	virtual void setMat2Array(const char* name, const glm::mat2 *mat, size_t count) const;
	virtual void setMat3Array(const char* name, const glm::mat3 *mat, size_t count) const;
	virtual void setMat4Array(const char* name, const glm::mat4 *mat, size_t count) const;

	virtual void bindTexture();
	virtual void bindTexture(Abstract::sTexture tex);
	virtual void bindTexture(Abstract::sFramebuffer tex) ;
	virtual void bindTexture(Abstract::sFont tex);
};

}
#endif // GLSHADERPROGRAM_HPP
