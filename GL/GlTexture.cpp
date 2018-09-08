#include "GlTexture.hpp"
#include <vector>
#include <cstring>
#include <stdexcept>
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
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textureID);
}
Texture::~Texture()
{
	glDeleteTextures(1,&textureID);
}
const std::array<const char*,Texture::texture_MAX> Texture::TEX_TYPES = {
	{"texture_diffuse",
	"texture_specular",
	"texture_normal",
	"texture_height"}
};

const char* Texture::stringizeType() const
{
	return TEX_TYPES[type % texture_MAX];
}

void Texture::bindTextureSide()
{
	glActiveTexture(textureID); // active proper texture unit before binding
	glBindTexture(GL_TEXTURE_2D, textureID);
}


Abstract::sTexture Texture::create(textureType ntype, sTextureConstructor constructor)
{
	if(!constructor) return nullptr;
	if(constructor->mipmaps.empty()) return nullptr;
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	Abstract::sTexture tmp = Abstract::sTexture(new Texture(ntype));
	Texture* gltex = dynamic_cast<Texture*>(tmp.get());
	gltex->height = constructor->mipmaps[0].height;
	gltex->width = constructor->mipmaps[0].width;
	gltex->linearSize = gltex->height * gltex->width;

	for(size_t i = 0; i < constructor->mipmaps.size(); ++i)
	{
		switch (constructor->type) {

		case Abstract::ImgType::RGB24:
		{
			glTexImage2D(GL_TEXTURE_2D, GLsizei(i),GL_RGB,
						 GLsizei(constructor->mipmaps[i].width),
						 GLsizei(constructor->mipmaps[i].height),
						 0,
						 GL_BGR,
						 GL_UNSIGNED_BYTE,
						 reinterpret_cast<GLvoid*>(constructor->mipmaps[i].pixelData.data()));
			break;
		}
		case Abstract::ImgType::RGBA32:
		{
			glTexImage2D(GL_TEXTURE_2D, GLsizei(i),GL_RGBA,
						 GLsizei(constructor->mipmaps[i].width),
						 GLsizei(constructor->mipmaps[i].height),
						 0,
						 GL_BGRA,
						 GL_UNSIGNED_BYTE,
						 reinterpret_cast<GLvoid*>(constructor->mipmaps[i].pixelData.data()));
			break;
		}
		case Abstract::ImgType::DDX1:
		{
			glCompressedTexImage2D(GL_TEXTURE_2D,
								   GLsizei(i),
								   GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
								   GLsizei(constructor->mipmaps[i].width),
								   GLsizei(constructor->mipmaps[i].height),
								   0,
								   GLsizei(constructor->mipmaps[i].pixelData.size()),
								   reinterpret_cast<GLvoid*>(constructor->mipmaps[i].pixelData.data()));
			break;
		}
		case Abstract::ImgType::DDX3:
		{
			glCompressedTexImage2D(GL_TEXTURE_2D,
								   GLsizei(i),
								   GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
								   GLsizei(constructor->mipmaps[i].width),
								   GLsizei(constructor->mipmaps[i].height),
								   0,
								   GLsizei(constructor->mipmaps[i].pixelData.size()),
								   reinterpret_cast<GLvoid*>(constructor->mipmaps[i].pixelData.data()));
			break;
		}
		case Abstract::ImgType::DDX5:
		{
			glCompressedTexImage2D(GL_TEXTURE_2D,
								   GLsizei(i),
								   GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
								   GLsizei(constructor->mipmaps[i].width),
								   GLsizei(constructor->mipmaps[i].height),
								   0,
								   GLsizei(constructor->mipmaps[i].pixelData.size()),
								   reinterpret_cast<GLvoid*>(constructor->mipmaps[i].pixelData.data()));
			break;
		}
		default: return nullptr;
		};
	}

	glFlush();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return tmp;
}

}
