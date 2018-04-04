#include "GlTexture.hpp"
#include <vector>
#include <cstring>
#include <stdexcept>
#include "../io/FreeImageIoExt.hpp"
namespace Gl {

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844
#define TGA_NO_IMAGE 0
#define TGA_COLORMAPPED 1
#define TGA_TRUECOLOUR 2
#define TGA_GREYSCALE 3
#define TGA_COMPRESSED 8
#define TGA_UNCOMPRESSED_COLORMAPPED TGA_COLORMAPPED
#define TGA_UNCOMPRESSED_TRUECOLOUR TGA_TRUECOLOUR
#define TGA_UNCOMPRESSED_GREYSCALE TGA_GREYSCALE
#define TGA_RUNLENGTH_COLORMAPPED (TGA_COLORMAPPED | TGA_COMPRESSED)
#define TGA_RUNLENGTH_TRUECOLOR (TGA_TRUECOLOUR | TGA_COMPRESSED)
#define TGA_RUNLENGTH_GREYSCALE (TGA_GREYSCALE | TGA_COMPRESSED)

Texture::Texture(textureType ntype)
	: type(ntype)
{
	glGenTextures(1, &textureID);
}
Texture::~Texture()
{
	glDeleteTextures(1,&textureID);
}


const char* Texture::__stringizeType(textureType typus)
{
	switch(typus)
	{
		case texture_diffuse:
	return "texture_diffuse";
	break;
		case texture_specular:
	return "texture_specular";
	break;
		case texture_normal:
	return "texture_normal";
	break;
		case texture_height:
	return "texture_height";
	break;
		default:
	return "invalid_texture";
	}
}
const char* Texture::stringizeType()
{
	return __stringizeType(type);
}

Abstract::sTexture Texture::createFromImage(textureType ntype, Abstract::sFIO reada)
{
	Abstract::sTexture tmp = Abstract::sTexture(new Texture(ntype));
	Texture* gltex = dynamic_cast<Texture*>(tmp.get());
	gltex->mipMapCount = 0;
	FlipImgExt img(reada);
	gltex->height = img.getHeight();
	gltex->width = img.getWidth();
	gltex->linearSize = gltex->height * gltex->width;
	// if(img.getBitsPerPixel() < 24) img.convertTo24Bits();
	glBindTexture(GL_TEXTURE_2D, gltex->textureID);
	if(img.isTransparent())
	{
		img.convertTo32Bits();
		std::vector<uint8_t> imgBuff(img.getHeight() * img.getWidth() * (img.getBitsPerPixel() / 8));
		FreeImage_ConvertToRawBits(imgBuff.data(),img,img.getScanWidth(),32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, true);
		glTexImage2D(GL_TEXTURE_2D, GL_RGBA, 0,gltex->width,gltex->height,0, GL_BGRA, GL_UNSIGNED_BYTE, imgBuff.data());
	}
	else
	{
		img.convertTo24Bits();
		std::vector<uint8_t> imgBuff(img.getHeight() * img.getWidth() * (img.getBitsPerPixel() / 8));
		FreeImage_ConvertToRawBits(imgBuff.data(),img,img.getScanWidth(),24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, true);
		glTexImage2D(GL_TEXTURE_2D, GL_RGB, 0,gltex->width,gltex->height,0, GL_BGR, GL_UNSIGNED_BYTE, imgBuff.data());
	}
	return tmp;
}

Abstract::sTexture Texture::createFromDDS(textureType ntype, Abstract::sFIO reada)
{
	Abstract::sTexture tmp = Abstract::sTexture(new Texture(ntype));
	Texture* gltex = dynamic_cast<Texture*>(tmp.get());
	std::vector<uint8_t> header(124);
	std::vector<char> mword(4);
	reada->read(mword.data(),4);
	if (strncmp(mword.data() , "DDS ", 4) != 0)
	{
		return Abstract::sTexture();
	}
	reada->read(header.data(),124);
	gltex->height = *reinterpret_cast<uint32_t*>(&header[8]);
	gltex->width = *reinterpret_cast<uint32_t*>(&header[12]);
	gltex->linearSize = *reinterpret_cast<uint32_t*>(&header[16]);
	gltex->mipMapCount = *reinterpret_cast<uint32_t*>(&header[24]);
	uint32_t fourCC = *reinterpret_cast<uint32_t*>(&header[80]);

	// Okay, now we will create the buffer.
	uint32_t buffsize = gltex->mipMapCount > 1 ? gltex->linearSize * 2 : gltex->linearSize;
	std::vector<uint8_t> buffer(buffsize);
	reada->read(buffer.data(),buffsize);

	uint32_t components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	uint32_t format;
	switch(fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		return Abstract::sTexture();
	}

	glBindTexture(GL_TEXTURE_2D, gltex->textureID);
	uint32_t blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	uint32_t offset = 0;
	uint32_t width = gltex->width;
	uint32_t height = gltex->height;

	for (uint32_t level = 0; level < gltex->mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer.data() + offset);

		offset += size;
		width  /= 2;
		height /= 2;
	}

	return tmp;
}

}
