#include "GlAnimatedCubemap.hpp"
#include "../io/GifIO.hpp"

namespace Gl {

AnimatedCubemap::AnimatedCubemap(uint32_t frameCount)
	: frames(frameCount)
{
	glGenTextures(frameCount,frames.data());
}
AnimatedCubemap::~AnimatedCubemap()
{
	glDeleteTextures(frames.size(),frames.data());
}
Abstract::sAnimatedCubemap AnimatedCubemap::create(Abstract::sFIO readah)
{
	GifIO gifio(readah);
	sAnimatedCubemap tmp = sAnimatedCubemap(new AnimatedCubemap(gifio.getImageCount()));
	GifIO::ImageCollection imgCol;
	gifio.resolveGif(imgCol);
	tmp->currFrame = 0;
	tmp->width = imgCol.x;
	tmp->height = imgCol.y / 6;
	tmp->linearSize = tmp->width * tmp->height;
	size_t i = 0;
	for(auto it = imgCol.images.begin(); it != imgCol.images.end(); ++it,++i)
	{
		if(!it->data()) throw std::runtime_error("Something went terribly wrong while trying to resolve the GIF!");
		size_t dataPtr = reinterpret_cast<size_t>(it->data());
		glBindTexture(GL_TEXTURE_CUBE_MAP, tmp->frames[i]);
		for(int i = 0; i < 6; ++i)
		{
			size_t offset = dataPtr + (i * (tmp->linearSize * sizeof(uint32_t)));
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,tmp->width,tmp->height,0,
			 GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, reinterpret_cast<GLvoid*>(offset));
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glFlush();
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		// glBindTexture(GL_TEXTURE_2D, 0);
	}
	return tmp;
}

uint32_t AnimatedCubemap::getWidth() const
{
	return width;
}
uint32_t AnimatedCubemap::getHeight() const
{
	return height;
}
uint32_t AnimatedCubemap::getLinearSize() const
{
	return linearSize;
}
uint32_t AnimatedCubemap::getFrameCount() const
{
	return uint32_t(frames.size());
}
void AnimatedCubemap::bindCubemapSide()
{
	glActiveTexture(frames[currFrame]); // active proper texture unit before binding
	glBindTexture(GL_TEXTURE_CUBE_MAP, frames[currFrame]);
}

}
