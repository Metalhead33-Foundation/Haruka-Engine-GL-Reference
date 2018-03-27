#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include "ShaderModule.hpp"

DEFINE_CLASS(ShaderProgram)
class ShaderProgram
{
public:
	virtual ~ShaderProgram() {;}
	virtual void pushModule(sShaderModule mod) = 0;
	virtual void popModule() = 0;
	virtual bool linkShaders() = 0;
};

#endif // SHADERPROGRAM_HPP
