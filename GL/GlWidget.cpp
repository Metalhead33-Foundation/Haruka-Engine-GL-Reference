#include "GlWidget.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Gl {
Widget::sQuad Widget::QUAD = nullptr;
void Widget::initializeQuad()
{
	QUAD = sQuad(new Quad());
}
void Widget::deinitializeQuad()
{
	QUAD = nullptr;
}
Widget::Quad::Quad()
{
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &quadArrayId);
	glGenBuffers(1, &quadBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, quadBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(quadArrayId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Widget::Quad::~Quad()
{
	glDeleteVertexArrays(1,&quadArrayId);
	glDeleteBuffers(1, &quadBufferId);
}
void Widget::Quad::draw()
{
	glBindVertexArray(quadArrayId);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

Abstract::sWidget Widget::create(int height, int width, Abstract::sTexture tex)
{
	return Abstract::sWidget(new Widget(height, width, tex));
}

Widget::Widget(int height, int width, Abstract::sTexture tex)
	: texture(tex)
{
	this->height = height;
	this->width = width;
	size.x = float(width);
	size.y = float(height);
}

void Widget::setWidth(int width)
{
	this->width = width;
	size.x = float(width);
}
void Widget::setHeight(int height)
{
	this->height = height;
	size.y = float(height);
}
int Widget::getWidth() const
{
	return width;
}
int Widget::getHeight() const
{
	return height;
}
void Widget::setTexture(Abstract::sTexture tex)
{
	texture = tex;
}
Abstract::sTexture Widget::getTexture()
{
	return texture;
}
void Widget::draw(Abstract::sShaderProgram shader, glm::vec2& position,
		  glm::mat4& projection)
{
	ShaderProgram* gshdr = dynamic_cast<ShaderProgram*>(shader.get());
	if(!gshdr) return;
	glUseProgram(gshdr->getShaderID());
	// Do the matrix stuff
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	gshdr->setMat4("projection", projection);
	gshdr->setMat4("model", model);
	Texture* tex;
	tex = dynamic_cast<Texture*>(texture.get());
	if(tex) {
		glActiveTexture(tex->getTextureId()); // active proper texture unit before binding
		glBindTexture(GL_TEXTURE_2D, tex->getTextureId());
		glUniform1i(glGetUniformLocation(gshdr->getShaderID(), tex->stringizeType()), 0);
	}
	// draw mesh
	QUAD->draw();

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

}
