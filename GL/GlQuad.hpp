#ifndef GLQUAD_HPP
#define GLQUAD_HPP
#include "../abstract/VertexProvider.hpp"
#include "GlVertexArray.hpp"
#include "GlVertexBufferObject.hpp"

namespace Gl {

DEFINE_STRUCT(Quad)
struct Quad : public Abstract::VertexProvider
{
	VertexArray VAO;
	VertexBufferObject VBO;
	Quad(bool framebuff=false);
	Quad(float upper, float lower, float left, float right);
	~Quad();
	void bind();
};

}
#endif // GLQUAD_HPP
