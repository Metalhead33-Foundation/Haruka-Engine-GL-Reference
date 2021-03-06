#include "GlAnimatedTexture.hpp"
#include "../io/GifIO.hpp"

namespace  Gl {

AnimatedTexture::AnimatedTexture(textureType ntype, uint32_t frameCount)
	: frames(frameCount), timer(0.00f), type(ntype), frameSwitchRate(1.0f/15.0f)
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(GLsizei(frames.size()),frames.data());
}
AnimatedTexture::~AnimatedTexture()
{
	glDeleteTextures(GLsizei(frames.size()),frames.data());
}
Abstract::sAnimatedTexture AnimatedTexture::create(textureType ntype, sAnimatedTextureConstructor constructor)
{
	if(!constructor) return nullptr;
	sAnimatedTexture tmp = sAnimatedTexture(new AnimatedTexture(ntype,constructor->frames.size()));

	tmp->currFrame = 0;
	tmp->mipMapCount = 0;
	tmp->width = constructor->width;
	tmp->height = constructor->height;
	tmp->linearSize = constructor->width * constructor->height;
	size_t i = 0;
	for(auto it = constructor->frames.begin(); it != constructor->frames.end(); ++it,++i)
	{
		if(it->data()){
		glBindTexture(GL_TEXTURE_2D, tmp->frames[i]);
		glTexImage2D(GL_TEXTURE_2D, // Target
					 0, // Level
					 GL_RGBA, // Internal format
					 tmp->width, // Width
					 tmp->height, // Height
					 0, // Border?
					 GL_RGBA, // Format?
					 GL_UNSIGNED_INT_8_8_8_8, // Type
					 reinterpret_cast<GLvoid*>(it->data()) // Actual pointer
					 );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glFlush();
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		// glBindTexture(GL_TEXTURE_2D, 0);
		} else throw std::runtime_error("Something went terribly wrong while trying to resolve the GIF!");
	}
	return tmp;
}
uint32_t AnimatedTexture::getWidth() const
{
	return width;
}
uint32_t AnimatedTexture::getHeight() const
{
	return height;
}
uint32_t AnimatedTexture::getLinearSize() const
{
	return linearSize;
}
uint32_t AnimatedTexture::getMipMapCount() const
{
	return 0;
}
uint32_t AnimatedTexture::getFrameCount() const
{
	return uint32_t(frames.size());
}
AnimatedTexture::textureType AnimatedTexture::getTextureType() const
{
	return type;
}
const char* AnimatedTexture::stringizeType() const
{
	return Gl::Texture::TEX_TYPES[type % texture_MAX];
}
void AnimatedTexture::bindTextureSide()
{
	glActiveTexture(frames[currFrame]); // active proper texture unit before binding
	glBindTexture(GL_TEXTURE_2D, frames[currFrame]);
}

}
