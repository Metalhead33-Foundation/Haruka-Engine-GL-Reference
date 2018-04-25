#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "ShaderModule.hpp"
#include <glm/glm.hpp>
namespace Abstract {

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
	virtual void setVec2(const char* name, const glm::vec2 &value) const = 0;
	virtual void setVec2(const char* name, float x, float y) const = 0;
	virtual void setVec3(const char* name, const glm::vec3 &value) const = 0;
	virtual void setVec3(const char* name, float x, float y, float z) const = 0;
	virtual void setVec4(const char* name, const glm::vec4 &value) const = 0;
	virtual void setVec4(const char* name, float x, float y, float z, float w) const = 0;
	virtual void setMat2(const char* name, const glm::mat2 &mat) const = 0;
	virtual void setMat3(const char* name, const glm::mat3 &mat) const = 0;
	virtual void setMat4(const char* name, const glm::mat4 &mat) const = 0;
	virtual void bindTexture(sTexture tex) = 0;

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
