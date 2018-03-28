#include "SoundFile.hpp"
#include <cstring>

SoundFile::SoundFile(sAbstractFread nhandle)
	: ioHandle(nhandle)
{
	sndInfo.channels;
	sndHandle = sf_open_virtual(&sndFileIO,SFM_READ,&sndInfo,reinterpret_cast<void*>(ioHandle.get()));
}
SoundFile::SoundFile(sAbstractFread nhandle, const SF_INFO& info)
	: ioHandle(nhandle)
{
	sndInfo = info;
	sndHandle = sf_open_virtual(&sndFileIO,SFM_READ,&sndInfo,reinterpret_cast<void*>(ioHandle.get()));
}
SoundFile::~SoundFile()
{
	sf_close(sndHandle);
}

sf_count_t SoundFile::seek(sf_count_t frames, int whence)
{
	return sf_seek(sndHandle,frames,whence);
}
int SoundFile::error()
{
	return sf_error(sndHandle);
}
const char* SoundFile::strerror()
{
	return sf_strerror(sndHandle);
}
int SoundFile::perror()
{
	return sf_perror(sndHandle);
}
int SoundFile::error_str(char* str, size_t len)
{
	return sf_error_str(sndHandle,str,len);
}
sf_count_t SoundFile::read_short (short *ptr, sf_count_t items)
{
	return sf_read_short(sndHandle,ptr,items);
}
sf_count_t SoundFile::read_int(int *ptr, sf_count_t items)
{
	return sf_read_int(sndHandle,ptr,items);
}
sf_count_t SoundFile::read_float (float *ptr, sf_count_t items)
{
	return sf_read_float(sndHandle,ptr,items);
}
sf_count_t SoundFile::read_double(double *ptr, sf_count_t items)
{
	return sf_read_double(sndHandle,ptr,items);
}

sf_count_t SoundFile::readf_short(short *ptr, sf_count_t frames)
{
	return sf_readf_short(sndHandle,ptr,frames);
}
sf_count_t SoundFile::readf_int(int *ptr, sf_count_t frames)
{
	return sf_readf_int(sndHandle,ptr,frames);
}
sf_count_t SoundFile::readf_float(float *ptr, sf_count_t frames)
{
	return sf_readf_float(sndHandle,ptr,frames);
}
sf_count_t SoundFile::readf_double(double *ptr, sf_count_t frames)
{
	return sf_readf_double(sndHandle,ptr,frames);
}
const char* SoundFile::get_string(int str_type)
{
	return sf_get_string(sndHandle,str_type);
}

/*
	  typedef sf_count_t  (*sf_vio_get_filelen) (void *user_data) ;
	  typedef sf_count_t  (*sf_vio_seek)        (sf_count_t offset, int whence, void *user_data) ;
	  typedef sf_count_t  (*sf_vio_read)        (void *ptr, sf_count_t count, void *user_data) ;
	  typedef sf_count_t  (*sf_vio_write)       (const void *ptr, sf_count_t count, void *user_data) ;
	  typedef sf_count_t  (*sf_vio_tell)        (void *user_data) ;
*/
sf_count_t sfGetFilelen(void *user_data);
sf_count_t sfSeek(sf_count_t offset, int whence, void *user_data);
sf_count_t sfRead(void *ptr, sf_count_t count, void *user_data);
sf_count_t sfTell(void *user_data);
SF_VIRTUAL_IO sndFileIO = { sfGetFilelen, sfSeek, sfRead, 0, sfTell };

sf_count_t sfGetFilelen(void *user_data)
{
	return reinterpret_cast<pAbstractFread>(user_data)->size();
}
sf_count_t sfSeek(sf_count_t offset, int whence, void *user_data)
{
	pAbstractFread chandle = reinterpret_cast<pAbstractFread>(user_data);
	switch(whence)
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
sf_count_t sfRead(void *ptr, sf_count_t count, void *user_data)
{
	return reinterpret_cast<pAbstractFread>(user_data)->read(ptr,count);
}
sf_count_t sfTell(void *user_data)
{
	return reinterpret_cast<pAbstractFread>(user_data)->tell();
}
