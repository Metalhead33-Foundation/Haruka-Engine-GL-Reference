#ifndef ANIMATEDTEXTURE_HPP
#define ANIMATEDTEXTURE_HPP
#include "Texture.hpp"
namespace Abstract {

DEFINE_CLASS(AnimatedTexture)
class AnimatedTexture : public Texture
{
public:
	virtual ~AnimatedTexture() = default;
	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
	virtual uint32_t getLinearSize() = 0;
	virtual uint32_t getMipMapCount() = 0;
	virtual uint32_t getFrameCount() = 0;
	virtual uint32_t getCurrentFrame() = 0;
	virtual void switchFrame(uint32_t newFrame) = 0;
	virtual float getFrameSwitchRate() = 0;
	virtual void setFrameSwitchRate(float newRate) = 0;
	virtual textureType getTextureType() const = 0;
	virtual const char* stringizeType() = 0;
	virtual void goForward(float forward) = 0;

	virtual void bindTextureSide() = 0;
};

}
#endif // ANIMATEDTEXTURE_HPP
