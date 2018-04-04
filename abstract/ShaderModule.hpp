#pragma once
#include "Global.hpp"
namespace Abstract {

DEFINE_CLASS(ShaderModule)
class ShaderModule
{
public:
	enum ShaderType : uint8_t
	{
		VERTEX_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		COMPUTE_SHADER
	};
	virtual ShaderType getType() = 0;
	virtual ~ShaderModule() = default;
};

}
