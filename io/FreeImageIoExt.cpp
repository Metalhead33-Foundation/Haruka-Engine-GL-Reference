#include "FreeImageIoExt.hpp"
#include <cstdio>
unsigned ImageRead(void* buffer, unsigned size, unsigned count, void* handle);
int ImageSeek(void* handle, long offset, int origin);
long ImageTell(void* handle);
FreeImageIO AbstractFreadImgio = { ImageRead, 0, ImageSeek, ImageTell };


FlipImgExt::FlipImgExt(sAbstractFread reedaa)
	: fhandle(reedaa)
{
	loadFromHandle(&AbstractFreadImgio,reinterpret_cast<void*>(fhandle.get()));
}

unsigned ImageRead(void* buffer, unsigned size, unsigned count, void* handle)
{
	return reinterpret_cast<pAbstractFread>(handle)->read(buffer,size*count);
}
int ImageSeek(void* handle, long offset, int origin)
{
	pAbstractFread chandle = reinterpret_cast<pAbstractFread>(handle);
	switch(origin)
	{
		case SEEK_SET:
			return chandle->seek(offset);
			break;
		case SEEK_CUR:
			return chandle->seek(chandle->tell() + offset);
			break;
		case SEEK_END:
			return chandle->seek(chandle->size() - offset);
			break;
		default:
			return 0;
	}
}
long ImageTell(void* handle)
{
	return reinterpret_cast<pAbstractFread>(handle)->tell();
}