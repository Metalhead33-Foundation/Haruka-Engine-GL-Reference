#include "GlCubeMap.hpp"
#include "../io/FreeImageIoExt.hpp"
#include <vector>

namespace Gl {

Cubemap::Cubemap()
{
	glGenTextures(1,&cubemapID);
}
Cubemap::~Cubemap()
{
	glDeleteTextures(1,&cubemapID);
}
void Cubemap::bindCubemapSide()
{
	glActiveTexture(cubemapID); // active proper texture unit before binding
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
}
Abstract::sCubemap Cubemap::create(Abstract::sFIO readah)
{
	sCubemap tmp = sCubemap(new Cubemap());
	sFlipImgExt img = FlipImgExt::createImageReader(readah);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tmp->cubemapID);
	tmp->width = img->getWidth();
	tmp->height = img->getHeight() / 6;
	tmp->linearSize = tmp->width * tmp->height;
	GLenum rgbFormatA = 0;
	GLenum rgbFormatB = 0;
	GLenum storageFormat = 0;
	if(img->isTransparent())
	{
		img->convertTo32Bits();
		rgbFormatA = GL_RGBA;
		rgbFormatB = GL_BGRA;
		storageFormat = GL_UNSIGNED_BYTE;
	}
	else
	{
		img->convertTo24Bits();
		rgbFormatA = GL_RGB;
		rgbFormatB = GL_BGR;
		storageFormat = GL_UNSIGNED_BYTE;
	}
	uint32_t absLine = 0;
	for(int i = 0; i < 6; ++i)
	{
		GLint imgType = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		glTexImage2D(imgType, 0, rgbFormatA,tmp->width,tmp->height,0,
		 rgbFormatB, storageFormat, NULL);
		if(img->isTransparent())
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		for(uint32_t relLine = 0; relLine < tmp->height; ++relLine, ++absLine)
		{
			glTexSubImage2D(imgType, 0, 0, relLine, tmp->width, 1, rgbFormatB, storageFormat, img->getScanLine(absLine));
		}
	}
	glFlush();
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return tmp;
}

}
