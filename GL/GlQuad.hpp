#ifndef GLQUAD_HPP
#define GLQUAD_HPP
#include "../abstract/Global.hpp"
#include "GlVertexArray.hpp"
#include "GlVertexBufferObject.hpp"

namespace Gl {

DEFINE_STRUCT(Quad)
struct Quad
{
	VertexArray VAO;
	VertexBufferObject VBO;
	Quad(bool framebuff=false);
	Quad(float upper, float lower, float left, float right);
	~Quad();
	void draw();
};

}
#endif // GLQUAD_HPP
