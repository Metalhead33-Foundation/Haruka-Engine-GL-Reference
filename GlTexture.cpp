#include "GlTexture.hpp"
#include <vector>
#include <cstring>
#include <stdexcept>

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

GlTexture::GlTexture(textureType ntype)
	: type(ntype)
{
	glGenTextures(1, &textureID);
}
GlTexture::~GlTexture()
{
	glDeleteTextures(1,&textureID);
}
sTexture GlTexture::createFromTGA(textureType ntype, sAbstractFread reada)
{
	sTexture tmp = sTexture(new GlTexture(ntype));
	GlTexture* gltex = dynamic_cast<GlTexture*>(tmp.get());
	gltex->mipMapCount = 0;
	uint8_t id;
	uint8_t cmapType;
	uint8_t imgType;
	uint16_t colormapFirstEntryIndex;
	uint16_t colormapLength;
	uint8_t colormapEntrySize;
	uint16_t xOrigin;
	uint16_t yOrigin;
	uint16_t imageWidth;
	uint16_t imageHeight;
	uint8_t pixelDepth;
	uint8_t imageDescriptor;

	reada->read(&id,sizeof(uint8_t));
	reada->read(&cmapType,sizeof(uint8_t));
	reada->read(&imgType,sizeof(uint8_t));
	// if((imgType & TGA_UNCOMPRESSED_COLORMAPPED) != 0) return sTexture();
	if((imgType & TGA_GREYSCALE) != 0) return sTexture();
	if((imgType & TGA_COMPRESSED) != 0) return sTexture();
	reada->read(&colormapFirstEntryIndex,sizeof(uint16_t));
	reada->read(&colormapLength,sizeof(uint16_t));
	reada->read(&colormapEntrySize,sizeof(uint8_t));
	reada->read(&xOrigin,sizeof(uint16_t));
	reada->read(&yOrigin,sizeof(uint16_t));
	reada->read(&imageWidth,sizeof(uint16_t));
	reada->read(&imageHeight,sizeof(uint16_t));
	reada->read(&pixelDepth,sizeof(uint8_t));
	reada->read(&imageDescriptor,sizeof(uint8_t));

	gltex->height = imageHeight;
	gltex->width = imageWidth;

	size_t byteRate = pixelDepth / 8;
	size_t imgSize = ((size_t)imageWidth * (size_t)imageHeight);
	gltex->linearSize = imgSize;
	imgSize *= byteRate;
	std::vector<uint8_t> pixelBuffer(imgSize);
	if((imgType & TGA_COMPRESSED) != 0)
	{
		uint8_t packetHeader;
		std::vector<uint8_t> individualPixel(byteRate);
		for(size_t offset = 0;offset < imgSize;) {
			reada->read(&packetHeader,sizeof(uint8_t));
			if( (packetHeader & 0x80) != 0)
			{
				uint8_t packetRepetition = packetHeader & 0x7F;
				reada->read(individualPixel.data(),byteRate);
				for(uint8_t flag = 0; flag < packetHeader; ++flag,offset+=byteRate)
				{
					memcpy(&(pixelBuffer[offset]),individualPixel.data(),byteRate);
				}
			}
			else
			{
				size_t readSize = byteRate * packetHeader;
				reada->read(&(pixelBuffer[offset]),readSize);
				offset += readSize;
			}
		}
	}
	else reada->read(pixelBuffer.data(),imgSize);
	glBindTexture(GL_TEXTURE_2D, gltex->textureID);
	switch(byteRate)
	{
	case 2:
		glTexImage2D(GL_TEXTURE_2D, GL_RGB5_A1, 0,imageWidth,imageHeight,0, GL_BGR, GL_UNSIGNED_BYTE, pixelBuffer.data());
		break;
	case 3:
		glTexImage2D(GL_TEXTURE_2D, GL_RGB, 0,imageWidth,imageHeight,0, GL_BGR, GL_UNSIGNED_BYTE, pixelBuffer.data());
		break;
	case 4:
		glTexImage2D(GL_TEXTURE_2D, GL_RGBA, 0,imageWidth,imageHeight,0, GL_BGRA, GL_UNSIGNED_BYTE, pixelBuffer.data());
		break;
	default:
		return sTexture();
		break;
	}
	return tmp;
}

sTexture GlTexture::createFromDDS(textureType ntype, sAbstractFread reada)
{
	sTexture tmp = sTexture(new GlTexture(ntype));
	GlTexture* gltex = dynamic_cast<GlTexture*>(tmp.get());
	std::vector<uint8_t> header(124);
	std::vector<char> mword(4);
	reada->read(mword.data(),4);
	if (strncmp(mword.data() , "DDS ", 4) != 0)
	{
		return sTexture();
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
		return sTexture();
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
