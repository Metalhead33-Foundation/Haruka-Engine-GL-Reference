#include "SoundFile.hpp"
#include <cstring>
namespace Audio {

sSoundFile SoundFile::createSoundFile(Abstract::sFIO nhandle, int mode,
	  int format, int channels, int samplerate)
{
	return sSoundFile(new SoundFile(nhandle,mode,format,channels,samplerate));
}
SoundFile::SoundFile(Abstract::sFIO nhandle, int mode,
					 int format, int channels, int samplerate)
	: ioHandle(nhandle),
	  SndfileHandle(sndFileIO,reinterpret_cast<void*>(nhandle.get()),mode,format,channels,samplerate)
{
	;
}
}
sf_count_t sfGetFilelen(void *user_data);
sf_count_t sfSeek(sf_count_t offset, int whence, void *user_data);
sf_count_t sfRead(void *ptr, sf_count_t count, void *user_data);
sf_count_t sfTell(void *user_data);
SF_VIRTUAL_IO sndFileIO = { sfGetFilelen, sfSeek, sfRead, 0, sfTell };

sf_count_t sfGetFilelen(void *user_data)
{
	return reinterpret_cast<Abstract::pFIO>(user_data)->size();
}
sf_count_t sfSeek(sf_count_t offset, int whence, void *user_data)
{
	Abstract::pFIO chandle = reinterpret_cast<Abstract::pFIO>(user_data);
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
	return reinterpret_cast<Abstract::pFIO>(user_data)->read(ptr,count);
}
sf_count_t sfTell(void *user_data)
{
	return reinterpret_cast<Abstract::pFIO>(user_data)->tell();
}
