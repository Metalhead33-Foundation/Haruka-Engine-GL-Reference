#ifndef GLANIMATEDTEXTURE_HPP
#define GLANIMATEDTEXTURE_HPP
#include "../abstract/AnimatedTexture.hpp"
#include "GlTexture.hpp"
#include "GlAnimated.hpp"
#include <vector>

namespace  Gl {

DEFINE_CLASS(AnimatedTexture)
class AnimatedTexture : public Abstract::AnimatedTexture, public Animated
{
private:
	std::vector<GLuint> frames;
	uint32_t width,height,linearSize,mipMapCount,currFrame;
	float frameSwitchRate;
	float timer;
	const textureType type;
	AnimatedTexture(textureType ntype, uint32_t frameCount);
public:
	static Abstract::sAnimatedTexture create(textureType ntype, Abstract::sFIO readah);
	~AnimatedTexture();
	uint32_t getWidth();
	uint32_t getHeight();
	uint32_t getLinearSize();
	uint32_t getMipMapCount();
	uint32_t getFrameCount();

	textureType getTextureType() const;
	const char* stringizeType();
	void bindTextureSide();
};

}
#endif // GLANIMATEDTEXTURE_HPP
