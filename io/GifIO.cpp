#include "GifIO.hpp"
#include <stdexcept>
#include <iostream>

GifIO::GifIO(Abstract::sFIO nIO)
	: fileIO(nIO), handle(0)
{
	int err = 0;
	handle = DGifOpen(fileIO.get(),&GifInput,&err);
	std::cout << err << " " << handle << std::endl;
	if(err) throw std::runtime_error("Error while loading a GIF!");
	DGifSlurp(handle);
	if(handle->Error) {
	std::cout << handle->Error << " " << handle << std::endl;
	throw std::runtime_error("Error while slurping a GIF!");
	}
	std::cout << "Created handle!" << std::endl;
}
GifIO::~GifIO()
{
	if(handle) DGifCloseFile(handle,nullptr);
}
int GifIO::GifInput(GifFileType* container, GifByteType* buffer, int size)
{
	if(!container) return -1;
	Abstract::pFIO filehandle = reinterpret_cast<Abstract::pFIO>(container->UserData);
	if(!filehandle) return -1;
	return int(filehandle->read(buffer,size));
}
GifWord GifIO::getWidth(void) const
{
	if(handle) return handle->SWidth;
	else return 0;
}
GifWord GifIO::getHeight(void) const
{
	if(handle) return handle->SHeight;
	else return 0;
}
int GifIO::getImageCount(void) const
{
	if(handle) return handle->ImageCount;
	else return 0;
}
void GifIO::resolveGif(Abstract::AnimatedImageContainer &coll)
{
	if(!handle) return;
	if(!(handle->ImageCount)) return;

	ColorMapObject *gifcolormap = handle->SColorMap;
	if(!gifcolormap) return;
	GifColorType *gifpalette = gifcolormap->Colors;
	if(!gifpalette) return;
	coll.width = handle->SWidth;
	coll.height = handle->SHeight;
	coll.frames.resize(size_t(handle->ImageCount));
	int transparency = -1;
	for(int i = 0; i < handle->ExtensionBlockCount; ++i)
	{
		std::cout << "*";
		GraphicsControlBlock block;
		if (DGifExtensionToGCB(handle->ExtensionBlocks[i].ByteCount,handle->ExtensionBlocks[i].Bytes,
							   &block)) {
		if(block.TransparentColor > transparency) transparency = block.TransparentColor;
		}
	}
	std::cout << std::endl;
	for(int i = 0; i < handle->ImageCount; ++i)
	{
		SavedImage* img = &(handle->SavedImages[i]);
		int newSize = img->ImageDesc.Height * img->ImageDesc.Width;
		coll.frames[i].resize(newSize);
		std::cout << coll.frames[i].size() << std::endl;
		std::cout << img->ImageDesc.Width << "x" << img->ImageDesc.Height << std::endl;
		for(int x = 0; x < newSize;++x)
		{
			if(transparency > 0 && img->RasterBits[x] == transparency)
			{
				coll.frames[i][x] = 0;
			}
			else coll.frames.at(i).at(x) = 255;
			coll.frames[i][x] = coll.frames[i][x] << 8;
			coll.frames[i][x] += gifpalette[img->RasterBits[x]].Green;
			coll.frames[i][x] = coll.frames[i][x] << 8;
			coll.frames[i][x] += gifpalette[img->RasterBits[x]].Blue;
			coll.frames[i][x] = coll.frames[i][x] << 8;
			coll.frames[i][x] += gifpalette[img->RasterBits[x]].Red;
			}
	}
	std::cout << "Prepared image!" << std::endl;
}
