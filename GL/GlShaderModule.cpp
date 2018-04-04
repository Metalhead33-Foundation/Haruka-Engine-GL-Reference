#include "GlShaderModule.hpp"
#include <stdexcept>
#include <vector>
namespace Gl {

const GLuint& ShaderModule::getShaderID() const
{
	return shaderID;
}
ShaderModule::ShaderType ShaderModule::getType()
{
	return type;
}
ShaderModule::~ShaderModule()
{
	glDeleteShader(shaderID); // Don't leak the shader.
}
Abstract::sShaderModule ShaderModule::createShaderModule(ShaderType ntype, Abstract::sFIO reada)
{
	return Abstract::sShaderModule(new ShaderModule(ntype, reada)) ;
}
ShaderModule::ShaderModule(ShaderType ntype, Abstract::sFIO reada)
	: type(ntype)
{
	switch(type) {
	case VERTEX_SHADER:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case TESS_CONTROL_SHADER:
		// shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
		// Tessalation control shader NOT supported!
		throw std::runtime_error("Tessalation control shader not supported!");
		break;
	case TESS_EVALUATION_SHADER:
		// shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
		// Tessalation evaluation shader NOT supported!
		throw std::runtime_error("Tessalation evaluation shader not supported!");
		break;
	case GEOMETRY_SHADER:
		shaderID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case FRAGMENT_SHADER:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case COMPUTE_SHADER:
		// shaderID = glCreateShader(GL_COMPUTE_SHADER);
		// Compute shader NOT supported!
		throw std::runtime_error("Compute shader not supported!");
		break;
	};
	std::vector<char> glslSrc;
	GLint len = reada->size();
	glslSrc.resize(len);
	reada->read(glslSrc.data(),len);
	const char* src = glslSrc.data();
	glShaderSource(shaderID,1,&src,&len);
	glCompileShader(shaderID);
	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		GLchar* errorLog = reinterpret_cast<GLchar*>(malloc(maxLength * sizeof(GLchar)));
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

		// Exit with failure.
		glDeleteShader(shaderID); // Don't leak the shader.
		throw std::runtime_error(errorLog);
	}
}

}
