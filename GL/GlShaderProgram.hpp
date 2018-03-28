#ifndef GLSHADERPROGRAM_HPP
#define GLSHADERPROGRAM_HPP
#include "../abstract/ShaderProgram.hpp"
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
	bool linkShaders();
	const GLuint& getShaderID() const;
};

#endif // GLSHADERPROGRAM_HPP
