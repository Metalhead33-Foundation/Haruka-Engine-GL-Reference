#include "SimpleWidgetViewProtoype.hpp"

SimpleWidgetViewProtoype::SimpleWidgetViewProtoype(const Abstract::sShaderProgram& shader)
	: TechniquePrototype(shader),
	  uniformLoc_model(shader->getLocation("model")),
	  uniformLoc_projection(shader->getLocation("projection")),
	  uniformLoc_texture(shader->getLocation("texture"))
{
	;
}
