#ifndef SIMPLEWIDGETVIEWWRAPPER_HPP
#define SIMPLEWIDGETVIEWWRAPPER_HPP
#include "AbstractTechniqueWrapper.hpp"
#include "../interface/SimpleWidgetViewInterface.hpp"
DEFINE_CLASS(SimpleWidgetViewWrapper)
class SimpleWidgetViewWrapper : public Abstract::TechniqueWrapper
{
protected:
	sSimpleWidgetViewInterface interface;
	glm::mat4 model;
	Abstract::sTexture texture;
public:
	static glm::mat4 PROJECTION;

	void run();
	const glm::mat4& getModelMatrix() const;
	const Abstract::sTexture& getTexture() const;
	const sSimpleWidgetViewInterface& getInterface() const;

	void setModelMatrix(const glm::mat4& setto);
	void setTexture(const Abstract::sTexture& setto);
	void setInterface(const sSimpleWidgetViewInterface& setto);
};

#endif // SIMPLEWIDGETVIEWWRAPPER_HPP
