#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP
#include <vector>
#include <deque>
#include "../abstract/Global.hpp"
/* OpenAL headers */
#include "OpenALWrapper.hpp"

namespace Audio {

DEFINE_CLASS(Context)
class Context
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
	Context(int nSamplerate);
	~Context();
	void makeCurrent();
	void process();
	void suspend();
	static const char* translateError(ALenum err);
	void logError(const char* classname, const char* operation, ALenum error);
};

}
#endif // AUDIOSYSTEM_HPP
