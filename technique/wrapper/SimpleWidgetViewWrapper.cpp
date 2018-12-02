#include "SimpleWidgetViewWrapper.hpp"

glm::mat4 SimpleWidgetViewWrapper::PROJECTION;

void SimpleWidgetViewWrapper::run()
{
	if(interface) interface->run(model,PROJECTION,texture);
}
const glm::mat4& SimpleWidgetViewWrapper::getModelMatrix() const
{
	return model;
}
const Abstract::sTexture& SimpleWidgetViewWrapper::getTexture() const
{
	return texture;
}
const sSimpleWidgetViewInterface& SimpleWidgetViewWrapper::getInterface() const
{
	return interface;
}

void SimpleWidgetViewWrapper::setModelMatrix(const glm::mat4& setto)
{
	model = setto;
}
void SimpleWidgetViewWrapper::setTexture(const Abstract::sTexture& setto)
{
	texture = setto;
}
void SimpleWidgetViewWrapper::setInterface(const sSimpleWidgetViewInterface& setto)
{
	interface = setto;
}
