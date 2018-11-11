#include "GlVertexArray.hpp"
namespace Gl {

GLuint VertexArray::boundId = 0;
VertexArray::VertexArray()
	: curIndex(0)
{
	glGenVertexArrays(1, &id);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1,&id);
}
bool VertexArray::isBound() const
{
	return boundId == id;
}
void VertexArray::bind() const
{
	if(!isBound())
	{
		glBindVertexArray(id);
		boundId = id;
	}
}
void VertexArray::unbind() const
{
	if(isBound())
	{
		glBindVertexArray(0);
		boundId = 0;
	}
}
void VertexArray::setAttribPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	bind();
	glEnableVertexAttribArray(curIndex);
	glVertexAttribPointer(curIndex, size, type, normalized, stride, pointer);
	++curIndex;
}
GLuint VertexArray::getIndex()
{
	return curIndex;
}

}
