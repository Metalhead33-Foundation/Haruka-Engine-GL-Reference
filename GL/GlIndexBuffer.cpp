#include "GlIndexBuffer.hpp"

namespace Gl {

IndexBuffer::IndexBuffer()
{

}

void IndexBuffer::bind() const
{
	ElementArrayBuffer::bind();
}
void IndexBuffer::unbind() const
{
	ElementArrayBuffer::unbind();
}
GLuint IndexBuffer::getId() const
{
	return ElementArrayBuffer::getId();
}
size_t IndexBuffer::getSize() const
{
	return ElementArrayBuffer::getSize();
}
size_t IndexBuffer::getIndexCount() const
{
	return indexCount;
}
void IndexBuffer::uploadIndices(const std::vector<unsigned int>& indices)
{
	indexCount = indices.size();
	ElementArrayBuffer::bufferData(indices.size()*sizeof(unsigned int),
								   indices.data(),
								   GL_STATIC_DRAW);
}

void IndexBuffer::draw()
{
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

}
