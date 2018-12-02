#ifndef SIMPLEWIDGETVIEWPROTOYPE_HPP
#define SIMPLEWIDGETVIEWPROTOYPE_HPP
#include "AbstractTechniquePrototype.hpp"
#include "../interface/SimpleWidgetViewInterface.hpp"
DEFINE_CLASS(SimpleWidgetViewProtoype)
class SimpleWidgetViewProtoype : public Abstract::TechniquePrototype, public SimpleWidgetViewInterface
{
protected:
	const int uniformLoc_model;
	const int uniformLoc_projection;
	const int uniformLoc_texture;
public:
	SimpleWidgetViewProtoype(const Abstract::sShaderProgram& shader);
	virtual ~SimpleWidgetViewProtoype() = default;
	virtual void run(const glm::mat4& model, const glm::mat4& projection,
					 const Abstract::sTexture& texture);
};

#endif // SIMPLEWIDGETVIEWPROTOYPE_HPP
