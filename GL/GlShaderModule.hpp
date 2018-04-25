#ifndef GLSHADERMODULE_HPP
#define GLSHADERMODULE_HPP
#include "../abstract/ShaderModule.hpp"
#include "../abstract/ShaderProgram.hpp"
#include "../abstract/FIO.hpp"
#include "glad_glx.h"

namespace Gl {
DEFINE_CLASS(ShaderModule)
class ShaderModule : public Abstract::ShaderModule
{
private:
	const ShaderType type;
	GLuint shaderID;
	ShaderModule(ShaderType ntype, Abstract::sFIO reada);
public:
	static Abstract::sShaderModule createShaderModule(ShaderType ntype, Abstract::sFIO reada);
	~ShaderModule();
	const GLuint& getShaderID() const;
	ShaderType getType();
};
}

#endif // GLSHADERMODULE_HPP
