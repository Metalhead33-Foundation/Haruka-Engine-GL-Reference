#ifndef GLCUBEMAP_HPP
#define GLCUBEMAP_HPP
#include "../abstract/Cubemap.hpp"
#include "glad_glx.h"
namespace Gl {

DEFINE_CLASS(Cubemap)
class Cubemap : public Abstract::Cubemap
{
public:
	friend class ShaderProgram;
private:
	GLuint cubemapID;
	uint32_t width,height,linearSize;
	Cubemap();
public:
	static Abstract::sCubemap create(Abstract::sFIO readah);
	~Cubemap();
	uint32_t getWidth() const { return width; }
	uint32_t getHeight() const { return height; }
	uint32_t getLinearSize() const { return linearSize; }
	void bindCubemapSide();
};

}
#endif // GLCUBEMAP_HPP
