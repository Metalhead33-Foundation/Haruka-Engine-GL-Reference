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
Abstract::sAnimatedTexture AnimatedTexture::create(textureType ntype, Abstract::sFIO readah)
{
	GifIO gifio(readah);
	sAnimatedTexture tmp = sAnimatedTexture(new AnimatedTexture(ntype,gifio.getImageCount()));

	GifIO::ImageCollection imgCol;
	gifio.resolveGif(imgCol);
	tmp->currFrame = 0;
	tmp->mipMapCount = 0;
	tmp->width = imgCol.x;
	tmp->height = imgCol.y;
	tmp->linearSize = imgCol.x * imgCol.y;
	std::cout << imgCol.x << "x" << imgCol.y << std::endl;
	size_t i = 0;
	for(auto it = imgCol.images.begin(); it != imgCol.images.end(); ++it,++i)
	{
		if(it->data()){
		std::cout << "Binding image! " << it->data() << std::endl;
		glBindTexture(GL_TEXTURE_2D, tmp->frames[i]);
		std::cout << "Adding texture!" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, // Target
					 0, // Level
					 GL_RGBA, // Internal format
					 imgCol.x, // Width
					 imgCol.y, // Height
					 0, // Border?
					 GL_RGBA, // Format?
					 GL_UNSIGNED_INT_8_8_8_8, // Type
					 reinterpret_cast<GLvoid*>(it->data()) // Actual pointer
					 );
		std::cout << "Added texture!" << std::endl;
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		std::cout << "Flushing texture!" << std::endl;
		glFlush();
		std::cout << "Flushed texture!" << std::endl;
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		// glBindTexture(GL_TEXTURE_2D, 0);
		std::cout << "Bound image!" << std::endl;
		} else throw std::runtime_error("Something went terribly wrong while trying to resolve the GIF!");
	}
	std::cout << "Bound textures!!" << std::endl;
	return tmp;
}
uint32_t AnimatedTexture::getWidth()
{
	return width;
}
uint32_t AnimatedTexture::getHeight()
{
	return height;
}
uint32_t AnimatedTexture::getLinearSize()
{
	return linearSize;
}
uint32_t AnimatedTexture::getMipMapCount()
{
	return 0;
}
uint32_t AnimatedTexture::getFrameCount()
{
	return uint32_t(frames.size());
}
uint32_t AnimatedTexture::getCurrentFrame()
{
	return currFrame;
}
void AnimatedTexture::switchFrame(uint32_t newFrame)
{
	currFrame = newFrame % frames.size();
}
float AnimatedTexture::getFrameSwitchRate()
{
	return frameSwitchRate;
}
void AnimatedTexture::setFrameSwitchRate(float newRate)
{
	frameSwitchRate = newRate;
}
AnimatedTexture::textureType AnimatedTexture::getTextureType() const
{
	return type;
}
const char* AnimatedTexture::stringizeType()
{
	return Gl::Texture::TEX_TYPES[type % texture_MAX];
}
void AnimatedTexture::bindTextureSide()
{
	glActiveTexture(frames[currFrame]); // active proper texture unit before binding
	glBindTexture(GL_TEXTURE_2D, frames[currFrame]);
}
void AnimatedTexture::goForward(float forward)
{
	timer += forward;
	while(timer >= frameSwitchRate)
	{
		++currFrame;
		timer -= frameSwitchRate;
	}
	currFrame %= frames.size();
}

}
