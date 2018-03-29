#ifndef SOUNDFILE_HPP
#define SOUNDFILE_HPP
#include "sndfile.hh"
#include "../abstract/AbstractFread.hpp"

DEFINE_CLASS(SoundFile)
class SoundFile : public SndfileHandle
{
private:
	const sAbstractFread ioHandle;
public:
	SoundFile(sAbstractFread nhandle, int mode = SFM_READ,
			  int format = 0, int channels = 0, int samplerate = 0);
};
extern SF_VIRTUAL_IO sndFileIO;

#endif // SOUNDFILE_HPP
