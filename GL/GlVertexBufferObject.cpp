#include "GlVertexBufferObject.hpp"

namespace Gl {

VertexBufferObject::VertexBufferObject()
{

}
void VertexBufferObject::bind() const
{
	ArrayBuffer::bind();
}
void VertexBufferObject::unbind() const
{
	ArrayBuffer::unbind();
}
void* VertexBufferObject::mapBuffer(GLenum access) const
{
	return ArrayBuffer::mapBuffer(access);
}
void* VertexBufferObject::mapBufferRange(GLintptr offset, GLsizeiptr size, GLbitfield access) const
{
	return ArrayBuffer::mapBufferRange(offset,size,access);
}
bool VertexBufferObject::unmapBuffer() const
{
	return ArrayBuffer::unmapBuffer();
}
void VertexBufferObject::flushBufferRange(GLintptr offset, GLsizeiptr size) const
{
	ArrayBuffer::flushBufferRange(offset,size);
}
GLuint VertexBufferObject::getId() const
{
	return ArrayBuffer::getId();
}
size_t VertexBufferObject::getSize() const
{
	return ArrayBuffer::getSize();
}
bool VertexBufferObject::isMapped() const
{
	return ArrayBuffer::isMapped();
}
// New functions
size_t VertexBufferObject::getVertexCount() const
{
	return vertexCount;
}
void VertexBufferObject::uploadVertices(const Abstract::VertexVector& vertices)
{
	vertexCount = vertices.size();
	ArrayBuffer::bufferData(vertices.size() * sizeof(Abstract::Vertex),
							vertices.data(),
							GL_STATIC_DRAW);
}

void VertexBufferObject::uploadVertices(const float *rawData, size_t dimensions, size_t vertexCount)
{
	this->vertexCount = vertexCount;
	ArrayBuffer::bufferData(dimensions * vertexCount * sizeof(float),
							rawData,
							GL_STATIC_DRAW);
}

void VertexBufferObject::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

}
