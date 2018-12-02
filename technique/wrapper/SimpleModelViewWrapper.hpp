#ifndef SIMPLEMODELVIEWWRAPPER_HPP
#define SIMPLEMODELVIEWWRAPPER_HPP
#include "AbstractTechniqueWrapper.hpp"
#include "../interface/SimpleModelViewInterface.hpp"

DEFINE_CLASS(SimpleModelViewWrapper)
class SimpleModelViewWrapper : public Abstract::TechniqueWrapper
{
protected:
	sSimpleModelViewInterface interface;
	GFX::sModel model;
	glm::mat4 modelMatrix;
	Abstract::sTexture texture;
public:
	void run();
	const GFX::sModel& getModel() const;
	const glm::mat4& getModelMatrix() const;
	const Abstract::sTexture& getTexture() const;
	const sSimpleModelViewInterface& getInterface() const;

	void setModel(const GFX::sModel& setto);
	void setModelMatrix(const glm::mat4& setto);
	void setTexture(const Abstract::sTexture& setto);
	void setInterface(const sSimpleModelViewInterface& setto);
};
#endif // SIMPLEMODELVIEWWRAPPER_HPP
