#ifndef GLSHADERMODULE_HPP
#define GLSHADERMODULE_HPP
#include "../abstract/ShaderModule.hpp"
#include "../abstract/AbstractFIO.hpp"
#include "glad_glx.h"

class GlShaderModule : public ShaderModule
{
private:
	const ShaderType type;
	GLuint shaderID;
public:
	GlShaderModule(ShaderType ntype, sAbstractFIO reada);
	~GlShaderModule();
	const GLuint& getShaderID() const;
	ShaderType getType();
};

#endif // GLSHADERMODULE_HPP
