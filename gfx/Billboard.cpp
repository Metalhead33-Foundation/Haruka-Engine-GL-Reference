#include "Billboard.hpp"
namespace GFX {

Billboard::Billboard()
	: drawable(nullptr), shader(nullptr)
{

}
void Billboard::render(const glm::mat4& projection)
{
	if(shader && drawable)
	{
		shader->useShader();
		shader->setVec3("CameraRight_worldspace",CameraRight_worldspace);
		shader->setVec3("CameraUp_worldspace",CameraUp_worldspace);
		shader->setVec3("pos",pos);
		shader->setVec2("size",size);
		drawable->render(projection,shader);
	}
}
const glm::mat4& Billboard::getModel() const
{
	return model;
}
const glm::vec3& Billboard::getPos() const
{
	return pos;
}
const glm::vec2 &Billboard::getSize() const
{
	return size;
}
void Billboard::setPos(const glm::vec3& npos)
{
	pos = npos;
}
void Billboard::setSize(const glm::vec2& nsize)
{
	size = nsize;
}
void Billboard::setModel(const glm::mat4& nmodel)
{
	model = nmodel;
}
float Billboard::getHeight() const
{
	return size.y;
}
float Billboard::getWidth() const
{
	return size.x;
}
void Billboard::setHeight(float setto)
{
	size.y = setto;
}
void Billboard::setWidth(float setto)
{
	size.x = setto;
}

void Billboard::updateWorldspace(const glm::mat4& viewMatrix)
{
	CameraRight_worldspace.x = viewMatrix[0][0];
	CameraRight_worldspace.y = viewMatrix[1][0];
	CameraRight_worldspace.z = viewMatrix[2][0];
	CameraUp_worldspace.x = viewMatrix[0][1];
	CameraUp_worldspace.y = viewMatrix[1][1];
	CameraUp_worldspace.z = viewMatrix[2][1];
}
Abstract::sDrawable Billboard::getDrawable() const
{
	return drawable;
}
Abstract::sShaderProgram Billboard::getShader() const
{
	return shader;
}
void Billboard::setDrawable(Abstract::sDrawable setto)
{
	drawable = setto;
}
void Billboard::setShader(Abstract::sShaderProgram setto)
{
	shader = setto;
}

}
