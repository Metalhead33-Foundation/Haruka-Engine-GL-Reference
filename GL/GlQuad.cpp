#include "GlQuad.hpp"
namespace Gl {

Quad::Quad(bool framebuff)
{
	glGenVertexArrays(1, &quadArrayId);
	glGenBuffers(1, &quadBufferId);
	glBindVertexArray(quadArrayId);
	glBindBuffer(GL_ARRAY_BUFFER, quadBufferId);
	if(framebuff) {
	GLfloat vertices[] = {
		// Pos      // Tex
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	} else
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
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Quad::Quad(float upper, float lower, float left, float right)
{
	glGenVertexArrays(1, &quadArrayId);
	glGenBuffers(1, &quadBufferId);
	glBindVertexArray(quadArrayId);
	glBindBuffer(GL_ARRAY_BUFFER, quadBufferId);
	GLfloat vertices[] = {
		// Pos      // Tex
		left,  upper,  0.0f, 1.0f,
		left, lower,  0.0f, 0.0f,
		right, upper,  1.0f, 0.0f,

		left,  upper,  0.0f, 1.0f,
		right, lower,  1.0f, 0.0f,
		right,  lower,  1.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Quad::~Quad()
{
	glDeleteVertexArrays(1,&quadArrayId);
	glDeleteBuffers(1, &quadBufferId);
}
void Quad::draw()
{
	glBindVertexArray(quadArrayId);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
}
