#ifndef GLSHADERMODULE_HPP
#define GLSHADERMODULE_HPP
#include "ShaderModule.hpp"
#include "AbstractFread.hpp"
#include "glad_glx.h"

class GlShaderModule : public ShaderModule
{
private:
	const ShaderType type;
	GLuint shaderID;
public:
	GlShaderModule(ShaderType ntype, sAbstractFread reada);
	~GlShaderModule();
	const GLuint& getShaderID() const;
	ShaderType getType();
};

#endif // GLSHADERMODULE_HPP
