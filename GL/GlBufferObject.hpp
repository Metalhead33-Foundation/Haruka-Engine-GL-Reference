#ifndef GLBUFFEROBJECT_HPP
#define GLBUFFEROBJECT_HPP
#include "glad.h"

namespace  Gl {

class BufferObject
{
protected:
	GLuint id;
	virtual bool isBound() const = 0;
	virtual void confirmBinding() const = 0;
	virtual void confirmUnbinding() const = 0;

	GLint getParamterI(GLenum param) const;
	bool getParamterB(GLenum param) const;
public:
	const GLenum type;
	BufferObject(const GLenum nType);
	virtual ~BufferObject();
	void bind() const;
	void unbind() const;
	void bufferData(GLsizei size, const void* data, GLenum usage) const;
	void bufferSubData(GLintptr offset, GLsizei size, const void* data) const;
	void* mapBuffer(GLenum access) const;
	void* mapBufferRange(GLintptr offset, GLsizeiptr size, GLbitfield access) const;
	bool unmapBuffer() const;
	void flushBufferRange(GLintptr offset, GLsizeiptr size) const;
	void getBufferSubData(GLintptr offset, GLsizeiptr size, void* data) const;

	GLuint getId() const;
	size_t getSize() const;
	bool isMapped() const;
};

template <GLenum target> class Buffer : public BufferObject
{
private:
	static GLuint bound;
protected:
	bool isBound() const
	{
		return bound == id;
	}
	void confirmBinding() const
	{
		bound = id;
	}
	void confirmUnbinding() const
	{
		bound = 0;
	}
public:
	Buffer()
		: BufferObject(target)
	{
		;
	}
};

typedef Buffer<GL_ARRAY_BUFFER> ArrayBuffer;
typedef Buffer<GL_ELEMENT_ARRAY_BUFFER> ElementArrayBuffer;
typedef Buffer<GL_TEXTURE_BUFFER> TextureBuffer;
typedef Buffer<GL_UNIFORM_BUFFER> UniformBuffer;

}
#endif // GLBUFFEROBJECT_HPP
