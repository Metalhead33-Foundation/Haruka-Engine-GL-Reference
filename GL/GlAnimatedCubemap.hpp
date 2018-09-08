#ifndef GLANIMATEDCUBEMAP_HPP
#define GLANIMATEDCUBEMAP_HPP
#include "../abstract/AnimatedCubemap.hpp"
#include "GlAnimated.hpp"
#include "GlCubeMap.hpp"
#include <vector>

namespace Gl {

DEFINE_CLASS(AnimatedCubemap)
class AnimatedCubemap : public Abstract::AnimatedCubemap, public Gl::Animated
{
private:
	std::vector<GLuint> frames;
	uint32_t width,height,linearSize;
	AnimatedCubemap(uint32_t frameCount);
public:
	static Abstract::sAnimatedCubemap create(sAnimatedTextureConstructor constructor);
	~AnimatedCubemap();
	uint32_t getFrameCount() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getLinearSize() const;
	void bindCubemapSide();
};

}
#endif // GLANIMATEDCUBEMAP_HPP
