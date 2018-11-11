#include "GlBufferObject.hpp"

namespace  Gl {

BufferObject::BufferObject(const GLenum nType)
	: type(nType)
{
	glGenBuffers(1,&id);
}
BufferObject::~BufferObject()
{
	glBindBuffer(type,0);
	glDeleteBuffers(1,&id);
}
void BufferObject::bind() const
{
	if(!isBound()) {
	glBindBuffer(type,id);
	confirmBinding();
	}
}
void BufferObject::unbind() const
{
	if(isBound()) {
	glBindBuffer(type,0);
	confirmUnbinding();
	}
}
GLint BufferObject::getParamterI(GLenum param) const
{
	bind();
	GLint tmp;
	glGetBufferParameteriv(type,param,&tmp);
	return tmp;
}
bool BufferObject::getParamterB(GLenum param) const
{
	bind();
	GLint tmp;
	glGetBufferParameteriv(type,param,&tmp);
	return tmp == GL_TRUE;
}
void BufferObject::bufferData(GLsizei size, const void* data, GLenum usage) const
{
	bind();
	glBufferData(type,size,data,usage);
}
void BufferObject::bufferSubData(GLintptr offset, GLsizei size, const void* data) const
{
	bind();
	glBufferSubData(type,offset,size,data);
}
void* BufferObject::mapBuffer(GLenum access) const
{
	bind();
	return glMapBuffer(type,access);
}
void* BufferObject::mapBufferRange(GLintptr offset, GLsizeiptr size, GLbitfield access) const
{
	bind();
	return glMapBufferRange(type,offset,size,access);
}
bool BufferObject::unmapBuffer() const
{
	bind();
	return glUnmapBuffer(type) == GL_TRUE;
}
void BufferObject::flushBufferRange(GLintptr offset, GLsizeiptr size) const
{
	bind();
	glFlushMappedBufferRange(type,offset,size);
}

GLuint BufferObject::getId() const
{
	return id;
}
size_t BufferObject::getSize() const
{
	return size_t(getParamterI(GL_BUFFER_SIZE));
}
bool BufferObject::isMapped() const
{
	return getParamterB(GL_BUFFER_MAPPED);
}

}
