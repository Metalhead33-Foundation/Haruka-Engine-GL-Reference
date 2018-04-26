#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP
#include "Texture.hpp"
namespace Abstract {

class Framebuffer : public Texture
{
public:
	virtual ~Framebuffer() = default;
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual void blit(Abstract::sFramebuffer buff = nullptr) = 0;
	virtual uint32_t getWidth() = 0;
	virtual uint32_t getHeight() = 0;
	virtual uint32_t getSampleCount() = 0;
};

}
#endif // FRAMEBUFFER_HPP
