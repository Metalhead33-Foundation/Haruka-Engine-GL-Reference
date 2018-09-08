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
Abstract::sCubemap Cubemap::create(sTextureConstructor constructor)
{
	sCubemap tmp = sCubemap(new Cubemap());
	glBindTexture(GL_TEXTURE_CUBE_MAP, tmp->cubemapID);
	tmp->width = constructor->mipmaps[0].width;
	tmp->height = constructor->mipmaps[0].height / 6;
	tmp->linearSize = tmp->width * tmp->height;

	for(size_t i = 0; i < constructor->mipmaps.size(); ++i)
	{
		switch (constructor->type) {

		case Abstract::ImgType::RGB24:
		{
			for(int j = 0; j < 6; ++j) {
			const size_t offset = tmp->height * j * tmp->width * 3;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, GLsizei(i),GL_RGB,
						 GLsizei(tmp->width),
						 GLsizei(tmp->height),
						 0,
						 GL_BGR,
						 GL_UNSIGNED_BYTE,
						 reinterpret_cast<GLvoid*>(&constructor->mipmaps[i].pixelData[offset]));
			}
			break;
		}
		case Abstract::ImgType::RGBA32:
		{
			for(int j = 0; j < 6; ++j) {
			const size_t offset = tmp->height * j * tmp->width * 4;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, GLsizei(i),GL_RGBA,
						 GLsizei(tmp->width),
						 GLsizei(tmp->height),
						 0,
						 GL_BGRA,
						 GL_UNSIGNED_BYTE,
						 reinterpret_cast<GLvoid*>(&constructor->mipmaps[i].pixelData[offset]));
			}
			break;
		}
		default: return nullptr;
		};
	}

	/*for(int i = 0; i < 6; ++i)
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
	}*/
	glFlush();
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return tmp;
}

}
