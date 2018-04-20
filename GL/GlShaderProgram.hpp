#ifndef GLSHADERPROGRAM_HPP
#define GLSHADERPROGRAM_HPP
#include "../abstract/ShaderProgram.hpp"
#include "GlShaderModule.hpp"
#include <deque>
namespace Gl {

class ShaderProgram : public Abstract::ShaderProgram
{
public:
	typedef std::deque<Abstract::sShaderModule> ModuleVector;
	typedef ModuleVector::iterator ModuleIterator;
private:
	GLuint shaderID;
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
	virtual void setVec2(const char* name, const glm::vec2 &value) const;
	virtual void setVec2(const char* name, float x, float y) const;
	virtual void setVec3(const char* name, const glm::vec3 &value) const;
	virtual void setVec3(const char* name, float x, float y, float z) const;
	virtual void setVec4(const char* name, const glm::vec4 &value) const;
	virtual void setVec4(const char* name, float x, float y, float z, float w) const;
	virtual void setMat2(const char* name, const glm::mat2 &mat) const;
	virtual void setMat3(const char* name, const glm::mat3 &mat) const;
	virtual void setMat4(const char* name, const glm::mat4 &mat) const;
};

}
#endif // GLSHADERPROGRAM_HPP
