#include "GlFramebuffer.hpp"

namespace  Gl {
Abstract::sFramebuffer Framebuffer::create(uint32_t nwidth, uint32_t nheight, uint32_t nsamples)
{
	Abstract::sFramebuffer tmp = Abstract::sFramebuffer(new Framebuffer(nwidth,nheight, nsamples));
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) return nullptr;
	else return tmp;
}

Framebuffer::Framebuffer(uint32_t nwidth, uint32_t nheight, uint32_t nsamples)
	: tex(sTexture(new Texture(Texture::texture_diffuse))), width(nwidth), height(nheight),
	  samples(nsamples), isMultisampled(samples != 0)
{
	glGenFramebuffers(1, &buffID);
	glGenRenderbuffers(1, &renderBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffID);
	tex->mipMapCount = 0;
	tex->height = height;
	tex->width = width;
	tex->linearSize = nheight * nwidth;
	if(isMultisampled) {
		glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, tex->textureID);
		glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, GLsizei(samples), GL_RGB, GLsizei(width),
								 GLsizei(height), false );
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, tex->textureID, 0);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	} else
	{
		glBindTexture(GL_TEXTURE_2D, tex->textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GLsizei(width), GLsizei(height), 0, GL_RGB,
					 GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->textureID, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, GLsizei(width), GLsizei(height));
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
Framebuffer::~Framebuffer()
{
	glDeleteRenderbuffers(1, &renderBuffer);
	glDeleteFramebuffers(1, &buffID);
}
void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, buffID);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glEnable(GL_DEPTH_TEST);
}
void Framebuffer::unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
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
	pFramebuffer nbuff = dynamic_cast<pFramebuffer>(buff.get());
	if(nbuff)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, nbuff->buffID);
	}
	else glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, buffID);
	glDrawBuffer(GL_BACK);
	glBlitFramebuffer(0, 0, GLint(width), GLint(height), 0, 0,
					  GLint(width), GLint(height), GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

}

