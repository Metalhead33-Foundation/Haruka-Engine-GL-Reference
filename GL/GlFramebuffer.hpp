#ifndef GLFRAMEBUFFER_HPP
#define GLFRAMEBUFFER_HPP
#include "GlTexture.hpp"
#include "../abstract/Framebuffer.hpp"

namespace  Gl {

class Framebuffer : public Abstract::Framebuffer
{
private:
	GLuint buffID;
	GLuint renderBuffer;
	GLuint tex;
	const uint32_t width, height, samples;
	Framebuffer(uint32_t nwidth, uint32_t nheight, uint32_t nsamples = 0);
	sFramebuffer blitter;
public:
	static Abstract::sFramebuffer create(uint32_t nwidth, uint32_t nheight, uint32_t nsamples = 0);
	~Framebuffer();
	void bind();
	void unbind();
	void blit(Abstract::sFramebuffer buff = nullptr);
	uint32_t getWidth();
	uint32_t getHeight();
	uint32_t getSampleCount();
	uint32_t getLinearSize();
	uint32_t getMipMapCount();
	textureType getTextureType() const;
	const char* stringizeType();
	void bindTextureSide();
};

}
#endif // GLFRAMEBUFFER_HPP
