#ifndef SOUNDFILE_HPP
#define SOUNDFILE_HPP
#include <sndfile.h>
#include "../abstract/AbstractFread.hpp"

DEFINE_CLASS(SoundFile)
class SoundFile
{
private:
	const sAbstractFread ioHandle;
	SNDFILE* sndHandle;
	SF_INFO sndInfo;
public:
	SoundFile(sAbstractFread nhandle);
	// SoundFile(sAbstractFread nhandle, const SF_INFO& info);
	~SoundFile();

	sf_count_t seek (sf_count_t frames, int whence);
	int error();
	const char* strerror();

	int perror();
	int error_str(char* str, size_t len);
	sf_count_t read_short (short *ptr, sf_count_t items);
	sf_count_t read_int(int *ptr, sf_count_t items);
	sf_count_t read_float (float *ptr, sf_count_t items);
	sf_count_t read_double (double *ptr, sf_count_t items);

	sf_count_t readf_short (short *ptr, sf_count_t frames);
	sf_count_t readf_int (int *ptr, sf_count_t frames);
	sf_count_t readf_float (float *ptr, sf_count_t frames);
	sf_count_t readf_double (double *ptr, sf_count_t frames);

	const char* get_string(int str_type) ;
};
extern SF_VIRTUAL_IO sndFileIO;

#endif // SOUNDFILE_HPP
