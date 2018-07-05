#ifndef GLINDEXBUFFER_HPP
#define GLINDEXBUFFER_HPP
#include "GlBufferObject.hpp"
#include <vector>

namespace Gl {

class IndexBuffer : private ElementArrayBuffer
{
private:
	size_t indexCount;
public:
	IndexBuffer();
	// Inherited functions
	void bind() const;
	void unbind() const;
	GLuint getId() const;
	size_t getSize() const;
	// new functions
	size_t getIndexCount() const;
	void uploadIndices(const std::vector<unsigned int> &indices);
	void draw();
};

}
#endif // GLINDEXBUFFER_HPP
