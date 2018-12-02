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
	GLint compilationStatus;
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
	virtual void setBool(int location, bool value) const;
	virtual void setInt(int location, int value) const;
	virtual void setFloat(int location, float value) const;
	virtual void setBvec2(int location, const glm::bvec2 &value) const;
	virtual void setBvec2(int location, bool x, bool y) const;
	virtual void setBvec3(int location, const glm::bvec3 &value) const;
	virtual void setBvec3(int location, bool x, bool y, bool z) const;
	virtual void setBvec4(int location, const glm::bvec4 &value) const;
	virtual void setBvec4(int location, bool x, bool y, bool z, bool w) const;
	virtual void setIvec2(int location, const glm::ivec2 &value) const;
	virtual void setIvec2(int location, int x, int y) const;
	virtual void setIvec3(int location, const glm::ivec3 &value) const;
	virtual void setIvec3(int location, int x, int y, int z) const;
	virtual void setIvec4(int location, const glm::ivec4 &value) const;
	virtual void setIvec4(int location, int x, int y, int z, int w) const;
	virtual void setVec2(int location, const glm::vec2 &value) const;
	virtual void setVec2(int location, float x, float y) const;
	virtual void setVec3(int location, const glm::vec3 &value) const;
	virtual void setVec3(int location, float x, float y, float z) const;
	virtual void setVec4(int location, const glm::vec4 &value) const;
	virtual void setVec4(int location, float x, float y, float z, float w) const;
	virtual void setMat2(int location, const glm::mat2 &mat) const;
	virtual void setMat3(int location, const glm::mat3 &mat) const;
	virtual void setMat4(int location, const glm::mat4 &mat) const;

	virtual void setBoolArray(int location, const bool *value, size_t count) const;
	virtual void setIntArray(int location, const int *value, size_t count) const;
	virtual void setFloatArray(int location, const float *value, size_t count) const;
	virtual void setBvec2Array(int location, const glm::bvec2 *value, size_t count) const;
	virtual void setBvec3Array(int location, const glm::bvec3 *value, size_t count) const;
	virtual void setBvec4Array(int location, const glm::bvec4 *value, size_t count) const;
	virtual void setIvec2Array(int location, const glm::ivec2 *value, size_t count) const;
	virtual void setIvec3Array(int location, const glm::ivec3 *value, size_t count) const;
	virtual void setIvec4Array(int location, const glm::ivec4 *value, size_t count) const;
	virtual void setVec2Array(int location, const glm::vec2 *value, size_t count) const;
	virtual void setVec3Array(int location, const glm::vec3 *value, size_t count) const;
	virtual void setVec4Array(int location, const glm::vec4 *value, size_t count) const;
	virtual void setMat2Array(int location, const glm::mat2 *mat, size_t count) const;
	virtual void setMat3Array(int location, const glm::mat3 *mat, size_t count) const;
	virtual void setMat4Array(int location, const glm::mat4 *mat, size_t count) const;

	virtual int getLocation(const char* name) const;
	virtual bool isValid() const;

	virtual void bindTexture(int location, Abstract::sTexture tex);
	virtual void bindTexture(int location, Abstract::sFramebuffer tex) ;
	virtual void bindTexture(int location, Abstract::sFont tex);
};

}
#endif // GLSHADERPROGRAM_HPP
