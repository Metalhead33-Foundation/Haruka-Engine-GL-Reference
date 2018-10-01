#include "FreeImageIoExt.hpp"
#include "../abstract/AbstractImageContainer.hpp"
#include "GifIO.hpp"
#include <webp/decode.h>
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

Abstract::sAnimatedImageContainer createFromGIF(Abstract::sFIO reada)
{
	GifIO gif(reada);
	Abstract::sAnimatedImageContainer tmp = Abstract::sAnimatedImageContainer(new Abstract::AnimatedImageContainer);
	gif.resolveGif(*tmp);
	tmp->type = Abstract::ImgType::RGBA32;
	return tmp;
}
Abstract::sAnimatedImageContainer createFromWEBP(Abstract::sFIO reada)
{
	auto buff = reada->loadIntoBuffer();
	if(WebPGetInfo(buff.data(),buff.size(),nullptr,nullptr))
	{
		WebPBitstreamFeatures feats;
		if(WebPGetFeatures(buff.data(),buff.size(),&feats) == VP8_STATUS_OK)
		{
			Abstract::sAnimatedImageContainer tmp = Abstract::sAnimatedImageContainer(new Abstract::AnimatedImageContainer);
			tmp->width = uint32_t(feats.width);
			tmp->height = uint32_t(feats.height);
			uint8_t* bitstream;
			size_t pixelDataSize;
			if(feats.has_alpha)
			{
				tmp->type = Abstract::ImgType::RGBA32;
				bitstream = WebPDecodeRGBA(buff.data(),buff.size(),&feats.width,&feats.height);
				pixelDataSize = size_t(feats.width * feats.height) * 4;

			}
			else
			{
				tmp->type = Abstract::ImgType::RGB24;
				bitstream = WebPDecodeRGB(buff.data(),buff.size(),&feats.width,&feats.height);
				pixelDataSize = size_t(feats.width * feats.height) * 3;
			}
			// We are supposed to do things with the image, load into the buffer, etc.
			WebPFree(bitstream);
			return tmp;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}

Abstract::sImageContainer createFromImage(Abstract::sFIO reada)
{
	if(reada) return nullptr;
	Abstract::sImageContainer tmp = Abstract::sImageContainer(new Abstract::ImageContainer);
	tmp->mipmaps.resize(1);
	sFlipImgExt img = FlipImgExt::createImageReader(reada);
	tmp->mipmaps[0].height = img->getHeight();
	tmp->mipmaps[0].width = img->getWidth();
	if(img->isTransparent())
	{
		tmp->type = Abstract::ImgType::RGBA32;
		img->convertTo32Bits();
		tmp->mipmaps[0].pixelData.resize(img->getHeight() * img->getWidth() * (img->getBitsPerPixel() / 8));
		FreeImage_ConvertToRawBits(tmp->mipmaps[0].pixelData.data(),*img,img->getScanWidth(),32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, true);
	}
	else
	{
		tmp->type = Abstract::ImgType::RGB24;
		img->convertTo24Bits();
		tmp->mipmaps[0].pixelData.resize(img->getHeight() * img->getWidth() * (img->getBitsPerPixel() / 8));
		FreeImage_ConvertToRawBits(tmp->mipmaps[0].pixelData.data(),*img,img->getScanWidth(),24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, true);
	}
	return tmp;
}

Abstract::sImageContainer createFromDDS(Abstract::sFIO reada)
{
	std::vector<uint8_t> header(124);
	std::vector<char> mword(4);
	reada->read(mword.data(),4);
	if (strncmp(mword.data() , "DDS ", 4) != 0)
	{
		return nullptr;
	}
	reada->read(header.data(),124);
	Abstract::sImageContainer tmp = Abstract::sImageContainer(new Abstract::ImageContainer);
	uint32_t height = *reinterpret_cast<uint32_t*>(&header[8]);
	uint32_t width = *reinterpret_cast<uint32_t*>(&header[12]);
	const uint32_t linearSize = *reinterpret_cast<uint32_t*>(&header[16]);
	const uint32_t mipMapCount = *reinterpret_cast<uint32_t*>(&header[24]);
	const uint32_t fourCC = *reinterpret_cast<uint32_t*>(&header[80]);

	switch(fourCC)
	{
	case FOURCC_DXT1:
		tmp->type = Abstract::ImgType::DDX1;
		break;
	case FOURCC_DXT3:
		tmp->type = Abstract::ImgType::DDX3;
		break;
	case FOURCC_DXT5:
		tmp->type = Abstract::ImgType::DDX5;
		break;
	default:
		return nullptr;
	}

	// Okay, now we will create the buffer.
	const uint32_t buffsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	std::vector<uint8_t> buffer(buffsize);
	reada->read(buffer.data(),buffsize);

	const uint32_t blockSize = (fourCC == fourCC) ? 8 : 16;
	uint32_t offset = 0;

	tmp->mipmaps.resize(mipMapCount);
	for (uint32_t level = 0; level < mipMapCount && (width || height); ++level)
	{
		const unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		tmp->mipmaps[level].height = height;
		tmp->mipmaps[level].width = width;
		tmp->mipmaps[level].pixelData.resize(size);
		memcpy(tmp->mipmaps[level].pixelData.data(),buffer.data() + offset,size);
		offset += size;
		width  /= 2;
		height /= 2;
	}

	return tmp;
}
