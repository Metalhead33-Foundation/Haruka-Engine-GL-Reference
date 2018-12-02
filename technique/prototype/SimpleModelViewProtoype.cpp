#include "SimpleModelViewProtoype.hpp"

SimpleModelViewProtoype::SimpleModelViewProtoype(const Abstract::sShaderProgram &shader)
	: TechniquePrototype(shader),
	  uniformLoc_modelMatrix(shader->getLocation("model")),
	  uniformLoc_texture(shader->getLocation("texture"))
{
	;
}

void SimpleModelViewProtoype::run(const GFX::sModel& model, const glm::mat4& modelMatrix,
				 const Abstract::sTexture& texture)
{
	if(shader && model && texture)
	{
		shader->useShader();
		shader->setMat4(uniformLoc_modelMatrix,modelMatrix);
		shader->bindTexture(uniformLoc_texture,texture);
		model->bind();
	}
}
