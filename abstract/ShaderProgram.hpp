#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "ShaderModule.hpp"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
namespace Abstract {

DEFINE_CLASS(Font)
DEFINE_CLASS(Framebuffer)
DEFINE_CLASS(Texture)
DEFINE_CLASS(ShaderProgram)
class ShaderProgram
{
public:
	friend class Texture;
	virtual ~ShaderProgram() = default;

	// Methods you need to implement

	virtual void pushModule(sShaderModule mod) = 0;
	virtual void popModule() = 0;
	virtual bool linkShaders() = 0;
	virtual void useShader() = 0;

	virtual void setBool(int location, bool value) const = 0;
	virtual void setInt(int location, int value) const = 0;
	virtual void setFloat(int location, float value) const = 0;
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
	virtual void setVec2(int location, const glm::vec2 &value) const = 0;
	virtual void setVec2(int location, float x, float y) const = 0;
	virtual void setVec3(int location, const glm::vec3 &value) const = 0;
	virtual void setVec3(int location, float x, float y, float z) const = 0;
	virtual void setVec4(int location, const glm::vec4 &value) const = 0;
	virtual void setVec4(int location, float x, float y, float z, float w) const = 0;
	virtual void setMat2(int location, const glm::mat2 &mat) const = 0;
	virtual void setMat3(int location, const glm::mat3 &mat) const = 0;
	virtual void setMat4(int location, const glm::mat4 &mat) const = 0;

	virtual void setBoolArray(int location, const bool *value, size_t count) const = 0;
	virtual void setIntArray(int location, const int *value, size_t count) const = 0;
	virtual void setFloatArray(int location, const float *value, size_t count) const = 0;
	virtual void setBvec2Array(int location, const glm::bvec2 *value, size_t count) const = 0;
	virtual void setBvec3Array(int location, const glm::bvec3 *value, size_t count) const = 0;
	virtual void setBvec4Array(int location, const glm::bvec4 *value, size_t count) const = 0;
	virtual void setIvec2Array(int location, const glm::ivec2 *value, size_t count) const = 0;
	virtual void setIvec3Array(int location, const glm::ivec3 *value, size_t count) const = 0;
	virtual void setIvec4Array(int location, const glm::ivec4 *value, size_t count) const = 0;
	virtual void setVec2Array(int location, const glm::vec2 *value, size_t count) const = 0;
	virtual void setVec3Array(int location, const glm::vec3 *value, size_t count) const = 0;
	virtual void setVec4Array(int location, const glm::vec4 *value, size_t count) const = 0;
	virtual void setMat2Array(int location, const glm::mat2 *mat, size_t count) const = 0;
	virtual void setMat3Array(int location, const glm::mat3 *mat, size_t count) const = 0;
	virtual void setMat4Array(int location, const glm::mat4 *mat, size_t count) const = 0;

	virtual void bindTexture(int location, sTexture tex) = 0;
	virtual void bindTexture(int location, sFramebuffer tex) = 0;
	virtual void bindTexture(int location, sFont tex) = 0;

	virtual bool isValid() const = 0;

	virtual int getLocation(const char* name) const = 0;

	// Inline methods
	inline int getLocation(const std::string& name) const { return getLocation(name.c_str()); }
};

}
#endif // SHADERPROGRAM_HPP
