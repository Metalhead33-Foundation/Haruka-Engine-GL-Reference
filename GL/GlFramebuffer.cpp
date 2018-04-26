#include "GlFramebuffer.hpp"
#include <stdexcept>

namespace  Gl {
Abstract::sFramebuffer Framebuffer::create(uint32_t nwidth, uint32_t nheight, uint32_t nsamples)
{
	Abstract::sFramebuffer tmp = Abstract::sFramebuffer(new Framebuffer(nwidth,nheight, nsamples));
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) return nullptr;
	else return tmp;
}

Framebuffer::Framebuffer(uint32_t nwidth, uint32_t nheight, uint32_t nsamples)
	: width(nwidth), height(nheight),
	  samples(nsamples), blitter(nullptr)
{
	glGenFramebuffers(1, &buffID);
	glGenRenderbuffers(1, &renderBuffer);
	glGenTextures(1,&tex);
	glBindFramebuffer(GL_FRAMEBUFFER, buffID);
	if(samples) {
		glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, tex);
		glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, GLsizei(samples), GL_RGB, GLsizei(width),
								 GLsizei(height), GL_TRUE );
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		// glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		// glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, tex, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, GLsizei(samples), GL_DEPTH24_STENCIL8, GLsizei(width), GLsizei(height));
	} else
	{
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GLsizei(width), GLsizei(height), 0, GL_RGB,
					 GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, GLsizei(width), GLsizei(height));
	}
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) throw std::runtime_error("Error creating the framebuffer!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if(samples)
	{
		blitter = sFramebuffer(new Framebuffer(nwidth, nheight, 0));
	}
}
Framebuffer::~Framebuffer()
{
	glDeleteRenderbuffers(1, &renderBuffer);
	glDeleteFramebuffers(1, &buffID);
	glDeleteTextures(1, &tex);
}
void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, buffID);
	// glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glEnable(GL_DEPTH_TEST);
}
void Framebuffer::unbind()
{
	// glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
}
uint32_t Framebuffer::getWidth()
{
	return width;
}
uint32_t Framebuffer::getHeight()
{
	return height;
}
uint32_t Framebuffer::getSampleCount()
{
	return samples;
}
void Framebuffer::blit(Abstract::sFramebuffer buff)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, buffID);
	pFramebuffer nbuff = dynamic_cast<pFramebuffer>(buff.get());
	if(nbuff)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, nbuff->buffID);
	}
	else {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glDrawBuffer(GL_FRONT_AND_BACK);
	}
	glBlitFramebuffer(0, 0, GLint(width), GLint(height), 0, 0,
					  GLint(width), GLint(height), GL_COLOR_BUFFER_BIT, GL_NEAREST);
	// if(glGetError() != GL_NO_ERROR)
	//	throw std::runtime_error("Error during blitting!");
}
void Framebuffer::resolveMultisample()
{
	if(blitter) blit(blitter);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
}
uint32_t Framebuffer::getLinearSize()
{
	return height * width;
}
uint32_t Framebuffer::getMipMapCount()
{
	return 0;
}
Framebuffer::textureType Framebuffer::getTextureType() const
{
	return texture_diffuse;
}
const char* Framebuffer::stringizeType()
{
	return Gl::Texture::TEX_TYPES[texture_diffuse];
}
void Framebuffer::bindTextureSide()
{
	if(blitter)
	{
		glActiveTexture(blitter->tex);
		glBindTexture(GL_TEXTURE_2D, blitter->tex);
	}
	else
	{
		glActiveTexture(tex); // active proper texture unit before binding
		if(samples)
		{
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, tex);
		}
	}
}

}

