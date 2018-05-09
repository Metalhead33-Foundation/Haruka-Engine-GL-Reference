#ifndef GLQUAD_HPP
#define GLQUAD_HPP
#include "../abstract/Global.hpp"
#include "glad_glx.h"

namespace Gl {

DEFINE_STRUCT(Quad)
struct Quad
{
	GLuint quadArrayId;
	GLuint quadBufferId;
	Quad(bool framebuff=false);
	Quad(float upper, float lower, float left, float right);
	~Quad();
	void draw();
};

}
#endif // GLQUAD_HPP
