#ifndef GLANIMATEDCUBEMAP_HPP
#define GLANIMATEDCUBEMAP_HPP
#include "../abstract/AnimatedCubemap.hpp"
#include "GlAnimated.hpp"
#include "GlCubeMap.hpp"
#include <vector>

namespace Gl {

DEFINE_CLASS(AnimatedCubemap)
class AnimatedCubemap : public Abstract::AnimatedCubemap, public Animated
{
private:
	std::vector<GLuint> frames;
	uint32_t width,height,linearSize;
	AnimatedCubemap(uint32_t frameCount);
public:
	static Abstract::sAnimatedCubemap create(Abstract::sFIO readah);
	~AnimatedCubemap();
	uint32_t getFrameCount();
	uint32_t getWidth();
	uint32_t getHeight();
	uint32_t getLinearSize();
	void bindCubemapSide();
};

}
#endif // GLANIMATEDCUBEMAP_HPP
