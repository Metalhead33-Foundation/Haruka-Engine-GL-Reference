#ifndef SIMPLEMODELVIEWPROTOYPE_HPP
#define SIMPLEMODELVIEWPROTOYPE_HPP
#include "AbstractTechniquePrototype.hpp"
#include "../interface/SimpleModelViewInterface.hpp"

DEFINE_CLASS(SimpleModelViewProtoype)
class SimpleModelViewProtoype : public Abstract::TechniquePrototype, public SimpleModelViewInterface
{
protected:
	// These are set immediately, in the constructor, and are immutable afterwards! I considered making these static.
	const int uniformLoc_modelMatrix;
	const int uniformLoc_texture;
public:
	SimpleModelViewProtoype(const Abstract::sShaderProgram& shader);
	virtual ~SimpleModelViewProtoype() = default;
	virtual void run(const GFX::sModel& model, const glm::mat4& modelMatrix,
					 const Abstract::sTexture& texture);
};

#endif // SIMPLEMODELVIEWPROTOYPE_HPP
