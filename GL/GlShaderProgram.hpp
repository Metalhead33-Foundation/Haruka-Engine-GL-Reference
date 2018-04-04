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
	ModuleVector modules;
	ShaderProgram();
public:
	static Abstract::sShaderProgram createShaderProgram();
	~ShaderProgram();
	void pushModule(Abstract::sShaderModule mod);
	void popModule();
	bool linkShaders();
	const GLuint& getShaderID() const;
};

}
#endif // GLSHADERPROGRAM_HPP
