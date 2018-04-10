#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP
#include <vector>
#include <deque>
#include "../abstract/Global.hpp"
/* OpenAL headers */
#include "al.h"
#include "alc.h"
#include "alext.h"

namespace Audio {

DEFINE_CLASS(AudioSystem)
class AudioSystem
{
public:
	struct ErrorLog
	{
		const char* classname;
		const char* operation;
		const char* error;
	};
	typedef std::deque<ErrorLog> ErrorVector;
	typedef ErrorVector::iterator ErrorIterator;
private:
	ALCdevice* device;
	ALCcontext* context;
	ErrorVector errors;
public:
	AudioSystem(int nSamplerate);
	~AudioSystem();
	static const char* translateError(ALenum err);
	void logError(const char* classname, const char* operation, ALenum error);
};

}
#endif // AUDIOSYSTEM_HPP
