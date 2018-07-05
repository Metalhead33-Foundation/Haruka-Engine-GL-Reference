#ifndef GLVERTEXARRAY_HPP
#define GLVERTEXARRAY_HPP
#include "glad.h"
#include "../abstract/Global.hpp"
namespace Gl {

class VertexArray
{
private:
	GLuint id;
	static GLuint boundId;
	GLuint curIndex;
public:
	VertexArray();
	~VertexArray();
	bool isBound() const;
	void bind() const;
	void unbind() const;
	void setAttribPointer(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
	GLuint getIndex();
};

}
#endif // GLVERTEXARRAY_HPP
