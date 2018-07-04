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
	virtual void pushModule(sShaderModule mod) = 0;
	virtual void popModule() = 0;
	virtual bool linkShaders() = 0;
	virtual void useShader() = 0;

	virtual void setBool(const char* name, bool value) const = 0;
	virtual void setInt(const char* name, int value) const = 0;
	virtual void setFloat(const char* name, float value) const = 0;
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
	virtual void setVec2(const char* name, const glm::vec2 &value) const = 0;
	virtual void setVec2(const char* name, float x, float y) const = 0;
	virtual void setVec3(const char* name, const glm::vec3 &value) const = 0;
	virtual void setVec3(const char* name, float x, float y, float z) const = 0;
	virtual void setVec4(const char* name, const glm::vec4 &value) const = 0;
	virtual void setVec4(const char* name, float x, float y, float z, float w) const = 0;
	virtual void setMat2(const char* name, const glm::mat2 &mat) const = 0;
	virtual void setMat3(const char* name, const glm::mat3 &mat) const = 0;
	virtual void setMat4(const char* name, const glm::mat4 &mat) const = 0;

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

	virtual void bindTexture() = 0;
	virtual void bindTexture(sTexture tex) = 0;
	virtual void bindTexture(sFramebuffer tex) = 0;
	virtual void bindTexture(sFont tex) = 0;

	/*void setBool(const std::string &name, bool value) const { setBool(name.c_str(),value); }
	void setInt(const std::string &name, int value) const { setInt(name.c_str(),value); }
	void setFloat(const std::string &name, float value) const { setFloat(name.c_str(),value); }
	void setVec2(const std::string &name, const glm::vec2 &value) const { setVec2(name.c_str(),value); }
	void setVec2(const std::string &name, float x, float y) const { setVec2(name.c_str(),x,y); }
	void setVec3(const std::string &name, const glm::vec3 &value) const { setVec3(name.c_str(),value); }
	void setVec3(const std::string &name, float x, float y, float z) const { setVec3(name.c_str(),x,y,z); }
	void setVec4(const std::string &name, const glm::vec4 &value) const { setVec4(name.c_str(),value); }
	void setVec4(const std::string &name, float x, float y, float z, float w) const { setVec4(name.c_str(),x,y,z,w); }
	void setMat2(const std::string &name, const glm::mat2 &mat) const { setMat2(name.c_str(),mat); }
	void setMat3(const std::string &name, const glm::mat3 &mat) const { setMat3(name.c_str(),mat); }
	void setMat4(const std::string &name, const glm::mat4 &mat) const { setMat4(name.c_str(),mat); }*/
};

}
#endif // SHADERPROGRAM_HPP
