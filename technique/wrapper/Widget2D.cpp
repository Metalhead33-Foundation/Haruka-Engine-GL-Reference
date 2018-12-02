#include "Widget2D.hpp"
#include <glm/gtc/matrix_transform.hpp>

Widget2D::Widget2D()
{

}

void Widget2D::updateModel()
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	setModelMatrix(model);
}
const glm::vec2& Widget2D::getPos() const
{
	return pos;
}
const glm::vec2& Widget2D::getSize() const
{
	return size;
}
float Widget2D::getRotation() const
{
	return rotation;
}

void Widget2D::setPos(const glm::vec2& setto, bool update)
{
	pos = setto;
	if(update) updateModel();
}
void Widget2D::setSize(const glm::vec2& setto, bool update)
{
	size = setto;
	if(update) updateModel();
}
void Widget2D::setRotation(float setto, bool update)
{
	rotation = setto;
	if(update) updateModel();
}
