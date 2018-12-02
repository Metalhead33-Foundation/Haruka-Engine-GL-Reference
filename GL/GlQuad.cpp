#include "GlQuad.hpp"
namespace Gl {

Quad::Quad(bool framebuff)
{
	VAO.bind();
	VBO.bind();
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
	VBO.uploadVertices(vertices,4,6);
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
		VBO.uploadVertices(vertices,4,6);
	}
	VAO.setAttribPointer(2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	VAO.setAttribPointer(2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	VBO.unbind();
	VAO.unbind();
}
Quad::Quad(float upper, float lower, float left, float right)
{
	VAO.bind();
	VBO.bind();
	GLfloat vertices[] = {
		// Pos      // Tex
		left,  upper,  0.0f, 1.0f,
		left, lower,  0.0f, 0.0f,
		right, upper,  1.0f, 0.0f,

		left,  upper,  0.0f, 1.0f,
		right, lower,  1.0f, 0.0f,
		right,  lower,  1.0f, 1.0f
	};
	VBO.uploadVertices(vertices,4,6);
	VAO.setAttribPointer(2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	VAO.setAttribPointer(2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	VBO.unbind();
	VAO.unbind();
}
Quad::~Quad()
{
	;
}
void Quad::bind()
{
	VAO.bind();
	VBO.draw();
	VAO.unbind();
}
}
