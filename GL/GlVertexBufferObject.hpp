#ifndef GLVERTEXBUFFEROBJECT_HPP
#define GLVERTEXBUFFEROBJECT_HPP
#include "GlBufferObject.hpp"
#include "../abstract/Vertex.hpp"

namespace Gl {

class VertexBufferObject : private ArrayBuffer
{
private:
	size_t vertexCount;
public:
	VertexBufferObject();
	// Inherited functions
	void bind() const;
	void unbind() const;
	void* mapBuffer(GLenum access) const;
	void* mapBufferRange(GLintptr offset, GLsizeiptr size, GLbitfield access) const;
	bool unmapBuffer() const;
	void flushBufferRange(GLintptr offset, GLsizeiptr size) const;
	GLuint getId() const;
	size_t getSize() const;
	bool isMapped() const;
	// New functions
	size_t getVertexCount() const;
	void uploadVertices(const Abstract::VertexVector &vertices);
	void uploadVertices(const float* rawData, size_t dimensions, size_t vertexCount);
	void draw();
};

}
#endif // GLVERTEXBUFFEROBJECT_HPP
