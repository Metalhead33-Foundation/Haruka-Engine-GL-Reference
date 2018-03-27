#ifndef GLSHADERPROGRAM_HPP
#define GLSHADERPROGRAM_HPP
#include "ShaderProgram.hpp"
#include "GlShaderModule.hpp"
#include <deque>

class GlShaderProgram : public ShaderProgram
{
public:
	typedef std::deque<sShaderModule> ModuleVector;
	typedef ModuleVector::iterator ModuleIterator;
private:
	GLuint shaderID;
	ModuleVector modules;
public:
	GlShaderProgram();
	~GlShaderProgram();
	void pushModule(sShaderModule mod);
	void popModule();
	void linkShaders();
	const GLuint& getShaderID() const;
};

#endif // GLSHADERPROGRAM_HPP
