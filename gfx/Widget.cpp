#include "Widget.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace GFX {

Widget::Widget()
{

}
void  Widget::updateModel(bool cascade)
{
	glm::mat4 model;
	glm::mat4 local_origin = glm::translate(this->origin, glm::vec3(pos, 0.0f));
	local_origin = glm::translate(local_origin, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	local_origin = glm::rotate(local_origin, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	local_origin = glm::translate(local_origin, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(local_origin, glm::vec3(size, 1.0f));
	this->model = model;
	if(cascade) for(auto it = subwidgets.begin(); it != subwidgets.end(); ++it)
	{
		if(it->second) it->second->updateModel(local_origin);
	}
}
void Widget::updateModel(const glm::mat4& norigin, bool cascade)
{
	this->origin = norigin;
	updateModel(cascade);
}
const glm::vec2& Widget::getPos() const
{
	return pos;
}
const glm::vec2& Widget::getSize() const
{
	return size;
}
float Widget::getRotation() const
{
	return rotation;
}
void Widget::setPos(const glm::vec2& npos, bool cascade)
{
	pos = npos;
	updateModel(cascade);
}
void Widget::setSize(const glm::vec2& nsize, bool cascade)
{
	size = nsize;
	updateModel(cascade);
}
void Widget::setRotation(float nrotation, bool cascade)
{
	rotation = nrotation;
	updateModel(cascade);
}
const Abstract::sDrawable Widget::getDrawable() const
{
	return drawable;
}
void Widget::setDrawable(Abstract::sDrawable ndrawable)
{
	drawable = ndrawable;
}
const Abstract::sShaderProgram Widget::getShader() const
{
	return shader;
}
void Widget::setShader(Abstract::sShaderProgram nshader)
{
	shader = nshader;
}
void Widget::render(const glm::mat4& projection)
{
	glm::mat4 nmodel = model * projection;
	if(shader && drawable) drawable->render(nmodel,shader);
	for(auto it = subwidgets.begin(); it != subwidgets.end(); ++it)
	{
		if(it->second) it->second->render(projection);
	}
}

}
